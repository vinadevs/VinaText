#!/usr/bin/env python3
"""
Extract editor language + theme data out of the C++ static tables into JSON.

Source of truth (before this change):
    src/EditorColorLight.h    namespace EditorColorLight
    src/EditorColorDark.h     namespace EditorColorDark

Both headers duplicate an identical block of per-language metadata (name,
extension, comment delimiters, keyword blob) and differ only in colour data.
This script deduplicates the shared half into data/languages.json and emits the
per-theme colour data into data/theme-light.json and data/theme-dark.json.

It is also the verification tool: --verify re-reads the generated JSON and
asserts it reproduces the C++ tables exactly. That is the only correctness
signal available until the Windows build runs in CI, since the MFC app cannot
be compiled on macOS/Linux.

Usage:
    python3 tools/extract_language_data.py            # generate + verify
    python3 tools/extract_language_data.py --verify   # verify only
"""

import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
LIGHT_H = os.path.join(ROOT, "src", "EditorColorLight.h")
DARK_H = os.path.join(ROOT, "src", "EditorColorDark.h")
SCILEXER_H = os.path.join(ROOT, "include", "scintilla", "SciLexer.h")
DATA_DIR = os.path.join(ROOT, "data")

META_FIELDS = {
    "language": "name",
    "extention": "extension",       # sic - the original spelling
    "commentline": "commentLine",
    "commentStart": "commentStart",
    "commentEnd": "commentEnd",
}

C_ESCAPES = {
    "\\\\": "\\", '\\"': '"', "\\'": "'", "\\n": "\n",
    "\\t": "\t", "\\r": "\r", "\\0": "\0",
}


def unescape(s):
    out, i = [], 0
    while i < len(s):
        if s[i] == "\\" and i + 1 < len(s):
            pair = s[i:i + 2]
            if pair in C_ESCAPES:
                out.append(C_ESCAPES[pair])
                i += 2
                continue
        out.append(s[i])
        i += 1
    return "".join(out)


def join_literals(blob):
    """Concatenate adjacent C string literals, as the compiler would."""
    return "".join(unescape(m) for m in re.findall(r'"((?:[^"\\]|\\.)*)"', blob))


def read(path):
    with open(path, encoding="utf-8", errors="strict") as f:
        return f.read()


def parse_sce_constants():
    """SCE_* symbol -> integer value, from Scintilla's own header."""
    out = {}
    for m in re.finditer(r"^#define\s+(SCE_[A-Z0-9_]+)\s+(\d+)", read(SCILEXER_H), re.M):
        out[m.group(1)] = int(m.group(2))
    return out


def parse_header(path):
    src = read(path)

    palette = {}
    for m in re.finditer(
        r"const\s+COLORREF\s+(\w+)\s*=\s*RGB\(\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+)\s*\)\s*;", src
    ):
        name, r, g, b = m.group(1), *map(int, m.groups()[1:])
        palette[name] = (r, g, b)

    meta = {}
    for m in re.finditer(
        r'static\s+CString\s+g_str_(\w+?)_(language|extention|commentline|commentStart|commentEnd)'
        r'\s*=\s*_T\(\s*"((?:[^"\\]|\\.)*)"\s*\)\s*;',
        src,
    ):
        lang, field, value = m.group(1), m.group(2), unescape(m.group(3))
        meta.setdefault(lang, {})[META_FIELDS[field]] = value

    keywords = {}
    for m in re.finditer(
        r'static\s+const\s+char\s*\*\s*g_(\w+?)_KeyWords\s*=\s*((?:\s*"(?:[^"\\]|\\.)*")+)\s*;', src
    ):
        keywords[m.group(1)] = join_literals(m.group(2))

    styles = {}
    for m in re.finditer(
        r"static\s+SScintillaColors\s+g_rgb_Syntax_(\w+)\s*\[\]\s*=\s*\{(.*?)\}\s*;", src, re.S
    ):
        lang, body = m.group(1), m.group(2)
        entries = []
        for sm in re.finditer(r"\{\s*(SCE_[A-Z0-9_]+|-1)\s*,\s*(\w+)\s*\}", body):
            symbol, colour = sm.group(1), sm.group(2)
            if symbol == "-1":          # sentinel terminator, not data
                continue
            entries.append((symbol, colour))
        styles[lang] = entries

    # g_str_plantext is a lone UI label, not a language block
    plaintext = None
    pm = re.search(r'static\s+CString\s+g_str_plantext\s*=\s*_T\(\s*"([^"]*)"\s*\)\s*;', src)
    if pm:
        plaintext = pm.group(1)

    return dict(palette=palette, meta=meta, keywords=keywords, styles=styles,
                plaintext=plaintext)


def hexcolor(rgb):
    return "#%02X%02X%02X" % rgb


def build():
    light, dark = parse_header(LIGHT_H), parse_header(DARK_H)
    sce = parse_sce_constants()
    problems = []

    # --- the shared half must genuinely be identical, or dedup is unsound ---
    if set(light["meta"]) != set(dark["meta"]):
        problems.append("language sets differ: light-only=%s dark-only=%s" % (
            sorted(set(light["meta"]) - set(dark["meta"])),
            sorted(set(dark["meta"]) - set(light["meta"]))))
    for lang in sorted(set(light["meta"]) & set(dark["meta"])):
        if light["meta"][lang] != dark["meta"][lang]:
            problems.append("metadata differs for %r" % lang)
    if set(light["keywords"]) != set(dark["keywords"]):
        problems.append("keyword language sets differ")
    for lang in sorted(set(light["keywords"]) & set(dark["keywords"])):
        if light["keywords"][lang] != dark["keywords"][lang]:
            problems.append("keywords differ for %r" % lang)
    # --- nothing in the C++ may be silently dropped on the way out ---
    for name, parsed in (("light", light), ("dark", dark)):
        orphan_kw = sorted(set(parsed["keywords"]) - set(parsed["meta"]))
        if orphan_kw:
            problems.append("%s: keyword blobs with no language metadata (would be "
                            "dropped from languages.json): %s" % (name, orphan_kw))

    if problems:
        raise SystemExit("Refusing to deduplicate:\n  " + "\n  ".join(problems))

    # Style tables with no language metadata are preserved in the theme files but
    # have no entry in languages.json. Faithful to the C++, but worth surfacing.
    orphan_styles = sorted(set(light["styles"]) - set(light["meta"]))
    no_keywords = sorted(set(light["meta"]) - set(light["keywords"]))
    empty_keywords = sorted(k for k, v in light["keywords"].items() if not v)
    for label, langs in (("style table but no language metadata", orphan_styles),
                         ("language metadata but no keyword blob", no_keywords),
                         ("keyword blob present but empty", empty_keywords)):
        if langs:
            print("note: %s: %s" % (label, ", ".join(langs)))

    languages = []
    for lang in sorted(light["meta"]):
        entry = {"id": lang}
        entry.update(light["meta"][lang])
        entry["keywords"] = light["keywords"].get(lang, "")
        languages.append(entry)

    languages_doc = {
        "_generatedBy": "tools/extract_language_data.py",
        "_source": "src/EditorColorLight.h, src/EditorColorDark.h (identical halves)",
        "plainTextLabel": light["plaintext"] or dark["plaintext"],
        "languages": languages,
    }

    themes = {}
    for name, parsed in (("light", light), ("dark", dark)):
        unknown = sorted({c for entries in parsed["styles"].values()
                          for _, c in entries if c not in parsed["palette"]})
        if unknown:
            raise SystemExit("theme %s references undefined colours: %s" % (name, unknown))
        themes[name] = {
            "_generatedBy": "tools/extract_language_data.py",
            "_source": "src/EditorColor%s.h" % name.capitalize(),
            "name": name,
            "palette": {k: hexcolor(v) for k, v in sorted(parsed["palette"].items())},
            "languages": {
                lang: [{"style": sym, "value": sce[sym], "color": col}
                       for sym, col in parsed["styles"][lang]]
                for lang in sorted(parsed["styles"])
            },
        }

    return languages_doc, themes, light, dark


def verify(languages_doc, themes, light, dark):
    """Re-derive the C++ tables from the JSON and compare, field by field."""
    failures = []
    by_id = {e["id"]: e for e in languages_doc["languages"]}

    for name, parsed in (("light", light), ("dark", dark)):
        theme = themes[name]

        if set(by_id) != set(parsed["meta"]):
            failures.append("%s: language set mismatch" % name)

        for lang, cpp in parsed["meta"].items():
            got = by_id.get(lang, {})
            for field, want in cpp.items():
                if got.get(field) != want:
                    failures.append("%s/%s.%s: %r != %r" % (name, lang, field, got.get(field), want))
            want_kw = parsed["keywords"].get(lang, "")
            if got.get("keywords", "") != want_kw:
                failures.append("%s/%s.keywords: %d chars != %d chars"
                                % (name, lang, len(got.get("keywords", "")), len(want_kw)))

        for lang, entries in parsed["styles"].items():
            got = theme["languages"].get(lang)
            if got is None:
                failures.append("%s/%s: missing style table" % (name, lang))
                continue
            if len(got) != len(entries):
                failures.append("%s/%s: %d styles != %d" % (name, lang, len(got), len(entries)))
                continue
            for i, (sym, col) in enumerate(entries):
                g = got[i]
                if g["style"] != sym or g["color"] != col:
                    failures.append("%s/%s[%d]: (%s,%s) != (%s,%s)"
                                    % (name, lang, i, g["style"], g["color"], sym, col))
                # the resolved RGB must match the C++ palette entry
                if theme["palette"].get(col) != hexcolor(parsed["palette"][col]):
                    failures.append("%s/%s[%d]: colour %s resolves differently" % (name, lang, i, col))
    return failures


def main():
    verify_only = "--verify" in sys.argv
    languages_doc, themes, light, dark = build()

    if not verify_only:
        os.makedirs(DATA_DIR, exist_ok=True)
        outputs = [("languages.json", languages_doc),
                   ("theme-light.json", themes["light"]),
                   ("theme-dark.json", themes["dark"])]
        for fname, doc in outputs:
            path = os.path.join(DATA_DIR, fname)
            with open(path, "w", encoding="utf-8") as f:
                json.dump(doc, f, indent=2, ensure_ascii=False)
                f.write("\n")
            print("wrote data/%-18s %7d bytes" % (fname, os.path.getsize(path)))

    # verify against what is actually on disk, not the in-memory objects
    on_disk = json.load(open(os.path.join(DATA_DIR, "languages.json"), encoding="utf-8"))
    on_disk_themes = {n: json.load(open(os.path.join(DATA_DIR, "theme-%s.json" % n), encoding="utf-8"))
                      for n in ("light", "dark")}
    failures = verify(on_disk, on_disk_themes, light, dark)

    n_styles = sum(len(v) for t in on_disk_themes.values() for v in t["languages"].values())
    print("\nlanguages: %d   keyword blobs: %d   style mappings: %d   palette entries: %d/%d"
          % (len(on_disk["languages"]),
             sum(1 for e in on_disk["languages"] if e["keywords"]),
             n_styles,
             len(on_disk_themes["light"]["palette"]), len(on_disk_themes["dark"]["palette"])))

    if failures:
        print("\nFAILED (%d):" % len(failures))
        for f in failures[:25]:
            print("  " + f)
        return 1
    print("round-trip verified: JSON reproduces both C++ tables exactly")
    return 0


if __name__ == "__main__":
    sys.exit(main())
