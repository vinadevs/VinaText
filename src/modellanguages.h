//--------------------------------
//---- normal Language
//--------------------------------
// language
static CString g_str_normal_language = _T("normal");
// extentions
static CString g_str_normal_extention = _T("normal");
// comment line
static CString g_str_normal_commentline = _T("");
// comment start
static CString g_str_normal_commentStart = _T("");
// comment end
static CString g_str_normal_commentEnd = _T("");
// keywords
static const char* g_normal_KeyWords =
// color text
static SScintillaColors g_rgb_Syntax_normal[] =
{ {} };

//--------------------------------
//---- actionscript Language
//--------------------------------
// language
static CString g_str_actionscript_language = _T("actionscript");
// extentions
static CString g_str_actionscript_extention = _T("actionscript");
// comment line
static CString g_str_actionscript_commentline = _T("//");
// comment start
static CString g_str_actionscript_commentStart = _T("/*");
// comment end
static CString g_str_actionscript_commentEnd = _T("*/");
// keywords
static const char* g_actionscript_KeyWords =
"add for lt tellTarget and function ne this break ge new typeof continue gt not var delete if on void do ifFrameLoaded onClipEvent while else in or with eq le return instanceof case default switch"
"arguments constructor class dynamic false extends implements import interface intrinsic newline null private public super static true undefined Accessibility Arguments Array Boolean Button Camera ContextMenu ContextMenuItem CustomActions Color Date Error Function Key LoadVars LocalConnection Math Microphone Mouse MovieClip MovieClipLoader NetConnection NetStream Number PrintJob Object TextField StyleSheet TextFormat TextSnapshot SharedObject Selection Sound Stage String System XML XMLNode XMLSocket Void abs acos asin atan atan2 ceil cos exp floor log max min pow random round sin sqrt tan onActivity onChanged onClose onConnect onData onDragOut onDragOver onEnterFrame onID3 onKeyDown onKeyUp onKillFocus onLoad onLoadComplete onLoadError onLoadInit onLoadProgress onLoadStart onMouseDown onMouseMove onMouseUp onMouseWheel onPress onRelease onReleaseOutside onResize onRollOut onRollOver onScroller onSelect onSetFocus onSoundComplete onStatus onUnload onUpdate onXML addListener addPage addProperty addRequestHeader allowDomain allowInsecureDomain appendChild apply applyChanges asfunction attachAudio attachMovie attachSound attachVideo beginFill beginGradientFill call charAt charCodeAt clear clearInterval cloneNode close concat connect copy createElement createEmptyMovieClip createTextField createTextNode curveTo domain duplicateMovieClip endFill escape eval evaluate findText fscommand flush fromCharCode get getAscii getBeginIndex getBounds getBytesLoaded getBytesTotal getCaretIndex getCode getCount getDate getDay getDepth getEndIndex getFocus getFontList getFullYear getHours getInstanceAtDepth getLocal getMilliseconds getMinutes getMonth getNewTextFormat getNextHighestDepth getPan getProggress getProperty getRGB getSeconds getSelected getSelectedText getSize getStyle getStyleNames getSWFVersion getText getTextExtent getTextFormat getTextSnapshot getTime getTimer getTimezoneOffset getTransform getURL getUTCDate getUTCDay getUTCFullYear getUTCHours getUTCMilliseconds getUTCMinutes getUTCMonth getUTCSeconds getVersion getVolume getYear globalToLocal gotoAndPlay gotoAndStop hasChildNodes hide hideBuiltInItems hitTest hitTestTextNearPos indexOf insertBefore install isActive isDown isToggled join lastIndexOf lineStyle lineTo list load loadClip loadMovie loadMovieNum loadSound loadVariables loadVariablesNum localToGlobal mbchr mblength mbord mbsubstring MMExecute moveTo nextFrame nextScene parseCSS parseFloat parseInt parseXML pause play pop prevScene print printAsBitmap printAsBitmapNum printNum push registerClass removeListener removeMovieClip removeNode removeTextField replaceSel replaceText reverse seek send sendAndLoad setBufferTime set setDate setFocus setFullYear setGain setHours setInterval setMask setMilliseconds setMinutes setMode setMonth setMotionLevel setNewTextFormat setPan setProperty setQuality setRate setRGB setSeconds setSelectColor setSelected setSelection setSilenceLevel setStyle setTextFormat setTime setTransform setUseEchoSuppression setUTCDate setUTCFullYear setUTCHours setUTCMilliseconds setUTCMinutes setUTCMonth setUTCSeconds setVolume setYear shift show showSettings silenceLevel silenceTimeout slice sort sortOn splice split start startDrag stop stopAllSounds stopDrag substr substring swapDepths toggleHighQuality toLowerCase toString toUpperCase trace unescape uninstall unLoadClip unloadMovie unloadMovieNum unshift unwatch updateAfterEvent updateProperties useEchoSuppression valueOf watch endinitclip include initclip __proto__ _accProps _alpha _currentframe _droptarget _focusrect _framesloaded _global _height _highquality _level _lockroot _name _parent _quality _root _rotation _soundbuftime _target _totalframes _url _visible _width _x _xmouse _xscale _y _ymouse _yscale activityLevel align attributes autoSize avHardwareDisable background backgroundColor bandwidth blockIndent bold border borderColor bottomScroll bufferLenght bufferTime builtInItems bullet bytesLoaded bytesTotal callee caller capabilities caption childNodes color condenseWhite contentType currentFps customItems data deblocking docTypeDecl duration embedFonts enabled exactSettings firstChild focusEnabled font fps gain globalStyleFormat hasAccessibility hasAudio hasAudioEncoder hasEmbeddedVideo hasMP3 hasPrinting hasScreenBroadcast hasScreenPlayback hasStreamingAudio hasStreamingVideo hasVideoEncoder height hitArea hscroll html htmlText indent index italic instanceof int ignoreWhite isDebugger isFinite language lastChild leading leftMargin length loaded localFileReadDisable manufacturer maxChars maxhscroll maxscroll menu message motionLevel motionTimeout mouseWheelEnabled multiline muted name names NaN nextSibling nodeName nodeType nodeValue os parentNode password pixelAspectRatio playerType previousSibling prototype quality rate restrict resolutionX resolutionY rightMargin scaleMode screenColor screenDPI screenResolutionX screenResolutionY scroll selectable separatorBefore showMenu size smoothing status styleSheet tabChildren tabEnabled tabIndex tabStops target targetPath text textColor textHeight textWidth time trackAsMenu type underline url useCodepage useHandCursor variable version visible width wordWrap xmlDecl"
"arguments constructor class dynamic false extends implements import interface intrinsic newline null private public super static true undefined Accessibility Arguments Array Boolean Button Camera ContextMenu ContextMenuItem CustomActions Color Date Error Function Key LoadVars LocalConnection Math Microphone Mouse MovieClip MovieClipLoader NetConnection NetStream Number PrintJob Object TextField StyleSheet TextFormat TextSnapshot SharedObject Selection Sound Stage String System XML XMLNode XMLSocket Void abs acos asin atan atan2 ceil cos exp floor log max min pow random round sin sqrt tan onActivity onChanged onClose onConnect onData onDragOut onDragOver onEnterFrame onID3 onKeyDown onKeyUp onKillFocus onLoad onLoadComplete onLoadError onLoadInit onLoadProgress onLoadStart onMouseDown onMouseMove onMouseUp onMouseWheel onPress onRelease onReleaseOutside onResize onRollOut onRollOver onScroller onSelect onSetFocus onSoundComplete onStatus onUnload onUpdate onXML addListener addPage addProperty addRequestHeader allowDomain allowInsecureDomain appendChild apply applyChanges asfunction attachAudio attachMovie attachSound attachVideo beginFill beginGradientFill call charAt charCodeAt clear clearInterval cloneNode close concat connect copy createElement createEmptyMovieClip createTextField createTextNode curveTo domain duplicateMovieClip endFill escape eval evaluate findText fscommand flush fromCharCode get getAscii getBeginIndex getBounds getBytesLoaded getBytesTotal getCaretIndex getCode getCount getDate getDay getDepth getEndIndex getFocus getFontList getFullYear getHours getInstanceAtDepth getLocal getMilliseconds getMinutes getMonth getNewTextFormat getNextHighestDepth getPan getProggress getProperty getRGB getSeconds getSelected getSelectedText getSize getStyle getStyleNames getSWFVersion getText getTextExtent getTextFormat getTextSnapshot getTime getTimer getTimezoneOffset getTransform getURL getUTCDate getUTCDay getUTCFullYear getUTCHours getUTCMilliseconds getUTCMinutes getUTCMonth getUTCSeconds getVersion getVolume getYear globalToLocal gotoAndPlay gotoAndStop hasChildNodes hide hideBuiltInItems hitTest hitTestTextNearPos indexOf insertBefore install isActive isDown isToggled join lastIndexOf lineStyle lineTo list load loadClip loadMovie loadMovieNum loadSound loadVariables loadVariablesNum localToGlobal mbchr mblength mbord mbsubstring MMExecute moveTo nextFrame nextScene parseCSS parseFloat parseInt parseXML pause play pop prevScene print printAsBitmap printAsBitmapNum printNum push registerClass removeListener removeMovieClip removeNode removeTextField replaceSel replaceText reverse seek send sendAndLoad setBufferTime set setDate setFocus setFullYear setGain setHours setInterval setMask setMilliseconds setMinutes setMode setMonth setMotionLevel setNewTextFormat setPan setProperty setQuality setRate setRGB setSeconds setSelectColor setSelected setSelection setSilenceLevel setStyle setTextFormat setTime setTransform setUseEchoSuppression setUTCDate setUTCFullYear setUTCHours setUTCMilliseconds setUTCMinutes setUTCMonth setUTCSeconds setVolume setYear shift show showSettings silenceLevel silenceTimeout slice sort sortOn splice split start startDrag stop stopAllSounds stopDrag substr substring swapDepths toggleHighQuality toLowerCase toString toUpperCase trace unescape uninstall unLoadClip unloadMovie unloadMovieNum unshift unwatch updateAfterEvent updateProperties useEchoSuppression valueOf watch endinitclip include initclip __proto__ _accProps _alpha _currentframe _droptarget _focusrect _framesloaded _global _height _highquality _level _lockroot _name _parent _quality _root _rotation _soundbuftime _target _totalframes _url _visible _width _x _xmouse _xscale _y _ymouse _yscale activityLevel align attributes autoSize avHardwareDisable background backgroundColor bandwidth blockIndent bold border borderColor bottomScroll bufferLenght bufferTime builtInItems bullet bytesLoaded bytesTotal callee caller capabilities caption childNodes color condenseWhite contentType currentFps customItems data deblocking docTypeDecl duration embedFonts enabled exactSettings firstChild focusEnabled font fps gain globalStyleFormat hasAccessibility hasAudio hasAudioEncoder hasEmbeddedVideo hasMP3 hasPrinting hasScreenBroadcast hasScreenPlayback hasStreamingAudio hasStreamingVideo hasVideoEncoder height hitArea hscroll html htmlText indent index italic instanceof int ignoreWhite isDebugger isFinite language lastChild leading leftMargin length loaded localFileReadDisable manufacturer maxChars maxhscroll maxscroll menu message motionLevel motionTimeout mouseWheelEnabled multiline muted name names NaN nextSibling nodeName nodeType nodeValue os parentNode password pixelAspectRatio playerType previousSibling prototype quality rate restrict resolutionX resolutionY rightMargin scaleMode screenColor screenDPI screenResolutionX screenResolutionY scroll selectable separatorBefore showMenu size smoothing status styleSheet tabChildren tabEnabled tabIndex tabStops target targetPath text textColor textHeight textWidth time trackAsMenu type underline url useCodepage useHandCursor variable version visible width wordWrap xmlDecl";
// color text
static SScintillaColors g_rgb_Syntax_actionscript[] =
{ {} };

//--------------------------------
//---- ada Language
//--------------------------------
// language
static CString g_str_ada_language = _T("ada");
// extentions
static CString g_str_ada_extention = _T("ada");
// comment line
static CString g_str_ada_commentline = _T("--");
// comment start
static CString g_str_ada_commentStart = _T("");
// comment end
static CString g_str_ada_commentEnd = _T("");
// keywords
static const char* g_ada_KeyWords =
"abort abs abstract accept access aliased all and array at begin body case constant declare delay delta digits do else elsif end entry exception exit for function generic goto if in interface is limited loop mod new not null of or others out overriding package pragma private procedure protected raise range record rem renames requeue return reverse select separate some subtype synchronized tagged task terminate then type until use when while with xor"
"abort abs abstract accept access aliased all and array at begin body case constant declare delay delta digits do else elsif end entry exception exit for function generic goto if in interface is limited loop mod new not null of or others out overriding package pragma private procedure protected raise range record rem renames requeue return reverse select separate some subtype synchronized tagged task terminate then type until use when while with xor";
// color text
static SScintillaColors g_rgb_Syntax_ada[] =
{ {} };

//--------------------------------
//---- asm Language
//--------------------------------
// language
static CString g_str_asm_language = _T("asm");
// extentions
static CString g_str_asm_extention = _T("asm");
// comment line
static CString g_str_asm_commentline = _T(";");
// comment start
static CString g_str_asm_commentStart = _T("");
// comment end
static CString g_str_asm_commentEnd = _T("");
// keywords
static const char* g_asm_KeyWords =
"aaa aad aam aas adc add and call cbw cdqe clc cld cli cmc cmp cmps cmpsb cmpsw cwd daa das dec div esc hlt idiv imul in inc int into iret ja jae jb jbe jc jcxz je jg jge jl jle jmp jna jnae jnb jnbe jnc jne jng jnge jnl jnle jno jnp jns jnz jo jp jpe jpo js jz lahf lds lea les lods lodsb lodsw loop loope loopew loopne loopnew loopnz loopnzw loopw loopz loopzw mov movabs movs movsb movsw mul neg nop not or out pop popf push pushf rcl rcr ret retf retn rol ror sahf sal sar sbb scas scasb scasw shl shr stc std sti stos stosb stosw sub test wait xchg xlat xlatb xor bound enter ins insb insw leave outs outsb outsw popa pusha pushw arpl lar lsl sgdt sidt sldt smsw str verr verw clts lgdt lidt lldt lmsw ltr bsf bsr bt btc btr bts cdq cmpsd cwde insd iretd iretdf iretf jecxz lfs lgs lodsd loopd looped loopned loopnzd loopzd lss movsd movsx movsxd movzx outsd popad popfd pushad pushd pushfd scasd seta setae setb setbe setc sete setg setge setl setle setna setnae setnb setnbe setnc setne setng setnge setnl setnle setno setnp setns setnz seto setp setpe setpo sets setz shld shrd stosd bswap cmpxchg invd invlpg wbinvd xadd lock rep repe repne repnz repz cflush cpuid emms femms cmovo cmovno cmovb cmovc cmovnae cmovae cmovnb cmovnc cmove cmovz cmovne cmovnz cmovbe cmovna cmova cmovnbe cmovs cmovns cmovp cmovpe cmovnp cmovpo cmovl cmovnge cmovge cmovnl cmovle cmovng cmovg cmovnle cmpxchg486 cmpxchg8b loadall loadall286 ibts icebp int1 int3 int01 int03 iretw popaw popfw pushaw pushfw rdmsr rdpmc rdshr rdtsc rsdc rsldt rsm rsts salc smi smint smintold svdc svldt svts syscall sysenter sysexit sysret ud0 ud1 ud2 umov xbts wrmsr wrshr"
"f2xm1 fabs fadd faddp fbld fbstp fchs fclex fcom fcomp fcompp fdecstp fdisi fdiv fdivp fdivr fdivrp feni ffree fiadd ficom ficomp fidiv fidivr fild fimul fincstp finit fist fistp fisub fisubr fld fld1 fldcw fldenv fldenvw fldl2e fldl2t fldlg2 fldln2 fldpi fldz fmul fmulp fnclex fndisi fneni fninit fnop fnsave fnsavew fnstcw fnstenv fnstenvw fnstsw fpatan fprem fptan frndint frstor frstorw fsave fsavew fscale fsqrt fst fstcw fstenv fstenvw fstp fstsw fsub fsubp fsubr fsubrp ftst fwait fxam fxch fxtract fyl2x fyl2xp1 fsetpm fcos fldenvd fnsaved fnstenvd fprem1 frstord fsaved fsin fsincos fstenvd fucom fucomp fucompp fcomi fcomip ffreep fcmovb fcmove fcmovbe fcmovu fcmovnb fcmovne fcmovnbe fcmovnu"
"ah al ax bh bl bp bx ch cl cr0 cr2 cr3 cr4 cs cx dh di dl dr0 dr1 dr2 dr3 dr6 dr7 ds dx eax ebp ebx ecx edi edx es esi esp fs gs rax rbx rcx rdx rdi rsi rbp rsp r8 r9 r10 r11 r12 r13 r14 r15 r8d r9d r10d r11d r12d r13d r14d r15d r8w r9w r10w r11w r12w r13w r14w r15w r8b r9b r10b r11b r12b r13b r14b r15b si sp ss st tr3 tr4 tr5 tr6 tr7 st0 st1 st2 st3 st4 st5 st6 st7 mm0 mm1 mm2 mm3 mm4 mm5 mm6 mm7 xmm0 xmm1 xmm2 xmm3 xmm4 xmm5 xmm6 xmm7 xmm8 xmm9 xmm10 xmm11 xmm12 xmm13 xmm14 xmm15"
".186 .286 .286c .286p .287 .386 .386c .386p .387 .486 .486p .8086 .8087 .alpha .break .code .const .continue .cref .data .data? .dosseg .else .elseif .endif .endw .err .err1 .err2 .errb .errdef .errdif .errdifi .erre .erridn .erridni .errnb .errndef .errnz .exit .fardata .fardata? .if .lall .lfcond .list .listall .listif .listmacro .listmacroall .model .no87 .nocref .nolist .nolistif .nolistmacro .radix .repeat .sall .seq .sfcond .stack .startup .tfcond .type .until .untilcxz .while .xall .xcref .xlist alias align assume catstr comm comment db dd df dosseg dq dt dup dw echo else elseif elseif1 elseif2 elseifb elseifdef elseifdif elseifdifi elseife elseifidn elseifidni elseifnb elseifndef end endif endm endp ends eq equ even exitm extern externdef extrn for forc ge goto group gt high highword if if1 if2 ifb ifdef ifdif ifdifi ife ifidn ifidni ifnb ifndef include includelib instr invoke irp irpc label le length lengthof local low lowword lroffset lt macro mask mod .msfloat name ne offset opattr option org %out page popcontext proc proto ptr public purge pushcontext record repeat rept seg segment short size sizeof sizestr struc struct substr subtitle subttl textequ this title type typedef union while width resb resw resd resq rest incbin times %define %idefine %xdefine %xidefine %undef %assign %iassign %strlen %substr %macro %imacro %endmacro %rotate %if %elif %else %endif %ifdef %ifndef %elifdef %elifndef %ifmacro %ifnmacro %elifmacro %elifnmacro %ifctk %ifnctk %elifctk %elifnctk %ifidn %ifnidn %elifidn %elifnidn %ifidni %ifnidni %elifidni %elifnidni %ifid %ifnid %elifid %elifnid %ifstr %ifnstr %elifstr %elifnstr %ifnum %ifnnum %elifnum %elifnnum %error %rep %endrep %exitrep %include %push %pop %repl endstruc istruc at iend alignb %arg %stacksize %local %line bits use16 use32 section absolute global common cpu import export"
"$ ? @b @f addr basic byte c carry? dword far far16 fortran fword near near16 overflow? parity? pascal qword real4 real8 real10 sbyte sdword sign? stdcall sword syscall tbyte vararg word zero? flat near32 far32 abs all assumes at casemap common compact cpu dotname emulator epilogue error export expr16 expr32 farstack forceframe huge language large listing ljmp loadds m510 medium memory nearstack nodotname noemulator nokeyword noljmp nom510 none nonunique nooldmacros nooldstructs noreadonly noscoped nosignextend nothing notpublic oldmacros oldstructs os_dos para private prologue radix readonly req scoped setif2 smallstack tiny use16 use32 uses a16 a32 o16 o32 nosplit $$ seq wrt small .text .data .bss %0 %1 %2 %3 %4 %5 %6 %7 %8 %9"
"addpd addps addsd addss andpd andps andnpd andnps cmpeqpd cmpltpd cmplepd cmpunordpd cmpnepd cmpnltpd cmpnlepd cmpordpd cmpeqps cmpltps cmpleps cmpunordps cmpneps cmpnltps cmpnleps cmpordps cmpeqsd cmpltsd cmplesd cmpunordsd cmpnesd cmpnltsd cmpnlesd cmpordsd cmpeqss cmpltss cmpless cmpunordss cmpness cmpnltss cmpnless cmpordss comisd comiss cvtdq2pd cvtdq2ps cvtpd2dq cvtpd2pi cvtpd2ps cvtpi2pd cvtpi2ps cvtps2dq cvtps2pd cvtps2pi cvtss2sd cvtss2si cvtsd2si cvtsd2ss cvtsi2sd cvtsi2ss cvttpd2dq cvttpd2pi cvttps2dq cvttps2pi cvttsd2si cvttss2si divpd divps divsd divss fxrstor fxsave ldmxscr lfence mfence maskmovdqu maskmovdq maxpd maxps paxsd maxss minpd minps minsd minss movapd movaps movdq2q movdqa movdqu movhlps movhpd movhps movd movq movlhps movlpd movlps movmskpd movmskps movntdq movnti movntpd movntps movntq movq2dq movsd movss movupd movups mulpd mulps mulsd mulss orpd orps packssdw packsswb packuswb paddb paddsb paddw paddsw paddd paddsiw paddq paddusb paddusw pand pandn pause paveb pavgb pavgw pavgusb pdistib pextrw pcmpeqb pcmpeqw pcmpeqd pcmpgtb pcmpgtw pcmpgtd pf2id pf2iw pfacc pfadd pfcmpeq pfcmpge pfcmpgt pfmax pfmin pfmul pmachriw pmaddwd pmagw pmaxsw pmaxub pminsw pminub pmovmskb pmulhrwc pmulhriw pmulhrwa pmulhuw pmulhw pmullw pmuludq pmvzb pmvnzb pmvlzb pmvgezb pfnacc pfpnacc por prefetch prefetchw prefetchnta prefetcht0 prefetcht1 prefetcht2 pfrcp pfrcpit1 pfrcpit2 pfrsqit1 pfrsqrt pfsub pfsubr pi2fd pinsrw psadbw pshufd pshufhw pshuflw pshufw psllw pslld psllq pslldq psraw psrad psrlw psrld psrlq psrldq psubb psubw psubd psubq psubsb psubsw psubusb psubusw psubsiw pswapd punpckhbw punpckhwd punpckhdq punpckhqdq punpcklbw punpcklwd punpckldq punpcklqdq pxor rcpps rcpss rsqrtps rsqrtss sfence shufpd shufps sqrtpd sqrtps sqrtsd sqrtss stmxcsr subpd subps subsd subss ucomisd ucomiss unpckhpd unpckhps unpcklpd unpcklps xorpd xorps"
"addpd addps addsd addss andpd andps andnpd andnps cmpeqpd cmpltpd cmplepd cmpunordpd cmpnepd cmpnltpd cmpnlepd cmpordpd cmpeqps cmpltps cmpleps cmpunordps cmpneps cmpnltps cmpnleps cmpordps cmpeqsd cmpltsd cmplesd cmpunordsd cmpnesd cmpnltsd cmpnlesd cmpordsd cmpeqss cmpltss cmpless cmpunordss cmpness cmpnltss cmpnless cmpordss comisd comiss cvtdq2pd cvtdq2ps cvtpd2dq cvtpd2pi cvtpd2ps cvtpi2pd cvtpi2ps cvtps2dq cvtps2pd cvtps2pi cvtss2sd cvtss2si cvtsd2si cvtsd2ss cvtsi2sd cvtsi2ss cvttpd2dq cvttpd2pi cvttps2dq cvttps2pi cvttsd2si cvttss2si divpd divps divsd divss fxrstor fxsave ldmxscr lfence mfence maskmovdqu maskmovdq maxpd maxps paxsd maxss minpd minps minsd minss movapd movaps movdq2q movdqa movdqu movhlps movhpd movhps movd movq movlhps movlpd movlps movmskpd movmskps movntdq movnti movntpd movntps movntq movq2dq movsd movss movupd movups mulpd mulps mulsd mulss orpd orps packssdw packsswb packuswb paddb paddsb paddw paddsw paddd paddsiw paddq paddusb paddusw pand pandn pause paveb pavgb pavgw pavgusb pdistib pextrw pcmpeqb pcmpeqw pcmpeqd pcmpgtb pcmpgtw pcmpgtd pf2id pf2iw pfacc pfadd pfcmpeq pfcmpge pfcmpgt pfmax pfmin pfmul pmachriw pmaddwd pmagw pmaxsw pmaxub pminsw pminub pmovmskb pmulhrwc pmulhriw pmulhrwa pmulhuw pmulhw pmullw pmuludq pmvzb pmvnzb pmvlzb pmvgezb pfnacc pfpnacc por prefetch prefetchw prefetchnta prefetcht0 prefetcht1 prefetcht2 pfrcp pfrcpit1 pfrcpit2 pfrsqit1 pfrsqrt pfsub pfsubr pi2fd pinsrw psadbw pshufd pshufhw pshuflw pshufw psllw pslld psllq pslldq psraw psrad psrlw psrld psrlq psrldq psubb psubw psubd psubq psubsb psubsw psubusb psubusw psubsiw pswapd punpckhbw punpckhwd punpckhdq punpckhqdq punpcklbw punpcklwd punpckldq punpcklqdq pxor rcpps rcpss rsqrtps rsqrtss sfence shufpd shufps sqrtpd sqrtps sqrtsd sqrtss stmxcsr subpd subps subsd subss ucomisd ucomiss unpckhpd unpckhps unpcklpd unpcklps xorpd xorps";
// color text
static SScintillaColors g_rgb_Syntax_asm[] =
{ {} };

//--------------------------------
//---- asn1 Language
//--------------------------------
// language
static CString g_str_asn1_language = _T("asn1");
// extentions
static CString g_str_asn1_extention = _T("asn1");
// comment line
static CString g_str_asn1_commentline = _T("");
// comment start
static CString g_str_asn1_commentStart = _T("");
// comment end
static CString g_str_asn1_commentEnd = _T("");
// keywords
static const char* g_asn1_KeyWords =
"ACCESS AGENT AUGMENTS BEGIN BITS CAPABILITIES CHOICE COMPLIANCE CONTACT CONVENTION DEFINITIONS DEFVAL DESCRIPTION DISPLAY END ENTERPRISE EXPORTS FALSE FROM GROUP GROUPS HINT IDENTITY IMPLIED IMPORTS INCLUDES INDEX INFO LAST MANDATORY MAX MIN MODULE NOTATION NOTIFICATION NULL OBJECTS OBJECT-TYPE OF ORGANIZATION PRODUCT RELEASE REFERENCE REQUIRES REVISION SEQUENCE SIZE STATUS SUPPORTS SYNTAX TEXTUAL TRAP TYPE TRAP-TYPE UPDATED VALUE VARIABLES VARIATION WRITE"
"accessible create current deprecated for mandatory not notify not-accessible obsolete only optional read read-only read-write write"
"ABSENT ANY APPLICATION BIT BOOLEAN BY COMPONENT COMPONENTS DEFAULT DEFINED ENUMERATED EXPLICIT EXTERNAL IMPLICIT INIFINITY MAX MIN MINUS OPTIONAL PRESENT PRIVATE REAL SET TAGS TRUE"
"Counter Counter32 Counter64 DisplayString Gauge Gauge32 IDENTIFIER INTEGER Integer32 IpAddress NetworkAddress NsapAddress OBJECT OCTET Opaque PhysAddress STRING TimeTicks UInteger32 UNITS Unsigned32"
"Counter Counter32 Counter64 DisplayString Gauge Gauge32 IDENTIFIER INTEGER Integer32 IpAddress NetworkAddress NsapAddress OBJECT OCTET Opaque PhysAddress STRING TimeTicks UInteger32 UNITS Unsigned32";
// color text
static SScintillaColors g_rgb_Syntax_asn1[] =
{ {} };

//--------------------------------
//---- asp Language
//--------------------------------
// language
static CString g_str_asp_language = _T("asp");
// extentions
static CString g_str_asp_extention = _T("asp");
// comment line
static CString g_str_asp_commentline = _T("'");
// comment start
static CString g_str_asp_commentStart = _T("");
// comment end
static CString g_str_asp_commentEnd = _T("");
// keywords
static const char* g_asp_KeyWords =
"addhandler addressof andalso alias and ansi as assembly attribute auto begin boolean byref byte byval call case catch cbool cbyte cchar cdate cdec cdbl char cint class clng cobj compare const continue cshort csng cstr ctype currency date decimal declare default delegate dim do double each else elseif end enum erase error event exit explicit false finally for friend function get gettype global gosub goto handles if implement implements imports in inherits integer interface is let lib like load long loop lset me mid mod module mustinherit mustoverride mybase myclass namespace new next not nothing notinheritable notoverridable object on option optional or orelse overloads overridable overrides paramarray preserve private property protected public raiseevent readonly redim rem removehandler rset resume return select set shadows shared short single static step stop string structure sub synclock then throw to true try type typeof unload unicode until variant wend when while with withevents writeonly xor"
"addhandler addressof andalso alias and ansi as assembly attribute auto begin boolean byref byte byval call case catch cbool cbyte cchar cdate cdec cdbl char cint class clng cobj compare const continue cshort csng cstr ctype currency date decimal declare default delegate dim do double each else elseif end enum erase error event exit explicit false finally for friend function get gettype global gosub goto handles if implement implements imports in inherits integer interface is let lib like load long loop lset me mid mod module mustinherit mustoverride mybase myclass namespace new next not nothing notinheritable notoverridable object on option optional or orelse overloads overridable overrides paramarray preserve private property protected public raiseevent readonly redim rem removehandler rset resume return select set shadows shared short single static step stop string structure sub synclock then throw to true try type typeof unload unicode until variant wend when while with withevents writeonly xor";
// color text
static SScintillaColors g_rgb_Syntax_asp[] =
{ {} };

//--------------------------------
//---- autoit Language
//--------------------------------
// language
static CString g_str_autoit_language = _T("autoit");
// extentions
static CString g_str_autoit_extention = _T("autoit");
// comment line
static CString g_str_autoit_commentline = _T(";");
// comment start
static CString g_str_autoit_commentStart = _T("#CS");
// comment end
static CString g_str_autoit_commentEnd = _T("#CE");
// keywords
static const char* g_autoit_KeyWords =
"and byref case const continuecase continueloop default dim do else elseif endfunc endif endselect endswitch enum exit exitloop false for func global if in local next not null or redim return select static step switch then to true until wend while"
"abs acos adlibdisable adlibenable asc asin atan autoitsetoption autoitwingettitle autoitwinsettitle bitand bitnot bitor bitshift bitxor blockinput break call cdtray chr clipget clipput controlclick controlcommand controldisable controlenable controlfocus controlgetfocus controlgetpos controlgettext controlhide controlmove controlsend controlsettext controlshow cos dec dircopy dircreate dirmove dirremove drivegetdrive drivegetfilesystem drivegetlabel drivegetserial drivegettype drivesetlabel drivespacefree drivespacetotal drivestatus envget envset envupdate eval exp filechangedir fileclose filecopy filecreateshortcut filedelete fileexists filefindfirstfile filefindnextfile filegetattrib filegetlongname filegetshortname filegetsize filegettime filegetversion fileinstall filemove fileopen fileopendialog fileread filereadline filerecycle filerecycleempty filesavedialog fileselectfolder filesetattrib filesettime filewrite filewriteline guicreate guicreateex guidefaultfont guidelete guigetcontrolstate guihide guimsg guiread guirecvmsg guisendmsg guisetcontrol guisetcontroldata guisetcontrolex guisetcontrolfont guisetcontrolnotify guisetcoord guisetcursor guishow guiwaitclose guiwrite hex hotkeyset inidelete iniread iniwrite inputbox int isadmin isarray isdeclared isfloat isint isnumber isstring log memgetstats mod mouseclick mouseclickdrag mousedown mousegetcursor mousegetpos mousemove mouseup mousewheel msgbox number pixelchecksum pixelgetcolor pixelsearch processclose processexists processsetpriority processwait processwaitclose progressoff progresson progressset random regdelete regenumkey regenumval regread regwrite round run runasset runwait send seterror shutdown sin sleep soundplay soundsetwavevolume splashimageon splashoff splashtexton sqrt statusbargettext string stringaddcr stringformat stringinstr stringisalnum stringisalpha stringisascii stringisdigit stringisfloat stringisint stringislower stringisspace stringisupper stringisxdigit stringleft stringlen stringlower stringmid stringreplace stringright stringsplit stringstripcr stringstripws stringtrimleft stringtrimright stringupper tan timerstart timerstop tooltip traytip ubound urldownloadtofile winactivate winactive winclose winexists wingetcaretpos wingetclasslist wingetclientsize wingethandle wingetpos wingetstate wingettext wingettitle winkill winmenuselectitem winminimizeall winminimizeallundo winmove winsetontop winsetstate winsettitle winwait winwaitactive winwaitclose winwaitnotactive"
"@appdatacommondir @appdatadir @autoitexe @autoitpid @autoitversion @autoitx64 @com_eventobj @commonfilesdir @compiled @computername @comspec @cpuarch @cr @crlf @desktopcommondir @desktopdepth @desktopdir @desktopheight @desktoprefresh @desktopwidth @documentscommondir @error @exitcode @exitmethod @extended @favoritescommondir @favoritesdir @gui_ctrlhandle @gui_ctrlid @gui_dragfile @gui_dragid @gui_dropid @gui_winhandle @homedrive @homepath @homeshare @hotkeypressed @hour @ipaddress1 @ipaddress2 @ipaddress3 @ipaddress4 @kblayout @lf @localappdatadir @logondnsdomain @logondomain @logonserver @mday @min @mon @msec @muilang @mydocumentsdir @numparams @osarch @osbuild @oslang @osservicepack @ostype @osversion @programfilesdir @programscommondir @programsdir @scriptdir @scriptfullpath @scriptlinenumber @scriptname @sec @startmenucommondir @startmenudir @startupcommondir @startupdir @sw_disable @sw_enable @sw_hide @sw_lock @sw_maximize @sw_minimize @sw_restore @sw_show @sw_showdefault @sw_showmaximized @sw_showminimized @sw_showminnoactive @sw_showna @sw_shownoactivate @sw_shownormal @sw_unlock @systemdir @tab @tempdir @tray_id @trayiconflashing @trayiconvisible @username @userprofiledir @wday @windowsdir @workingdir @yday @year"
"{!} {#} {^} {{} {}} {+} {alt} {altdown} {altup} {appskey} {asc} {backspace} {browser_back} {browser_favorites} {browser_forward} {browser_home} {browser_refresh} {browser_search} {browser_stop} {bs} {capslock} {ctrlbreak} {ctrldown} {ctrlup} {del} {delete} {down} {end} {enter} {esc} {escape} {f1} {f10} {f11} {f12} {f2} {f3} {f4} {f5} {f6} {f7} {f8} {f9} {home} {ins} {insert} {lalt} {launch_app1} {launch_app2} {launch_mail} {launch_media} {lctrl} {left} {lshift} {lwin} {lwindown} {media_next} {media_play_pause} {media_prev} {media_stop} {numlock} {numpad0} {numpad1} {numpad2} {numpad3} {numpad4} {numpad5} {numpad6} {numpad7} {numpad8} {numpad9} {numpadadd} {numpaddiv} {numpaddot} {numpadenter} {numpadmult} {numpadsub} {pause} {pgdn} {pgup} {printscreen} {ralt} {rctrl} {right} {rshift} {rwin} {rwindown} {scrolllock} {shiftdown} {shiftup} {sleep} {space} {tab} {up} {volume_down} {volume_mute} {volume_up}"
"#include #include-once #pragma"
"#region #endregion"
""
"";
// color text
static SScintillaColors g_rgb_Syntax_autoit[] =
{ {} };

//--------------------------------
//---- avs Language
//--------------------------------
// language
static CString g_str_avs_language = _T("avs");
// extentions
static CString g_str_avs_extention = _T("avs");
// comment line
static CString g_str_avs_commentline = _T("#");
// comment start
static CString g_str_avs_commentStart = _T("/*");
// comment end
static CString g_str_avs_commentEnd = _T("*/");
// keywords
static const char* g_avs_KeyWords =
"true false return global"
"addborders alignedsplice amplify amplifydb animate applyrange assumebff assumefieldbased assumefps assumeframebased assumesamplerate assumescaledfps assumetff audiodub audiodubex avifilesource avisource bicubicresize bilinearresize blackmanresize blackness blankclip blur bob cache changefps colorbars colorkeymask coloryuv compare complementparity conditionalfilter conditionalreader convertaudio convertaudioto16bit convertaudioto24bit convertaudioto32bit convertaudioto8bit convertaudiotofloat convertbacktoyuy2 convertfps converttobackyuy2 converttomono converttorgb converttorgb24 converttorgb32 converttoy8 converttoyv16 converttoyv24 converttoyv411 converttoyuy2 converttoyv12 crop cropbottom delayaudio deleteframe dissolve distributor doubleweave duplicateframe ensurevbrmp3sync fadein fadein0 fadein2 fadeio fadeio0 fadeio2 fadeout fadeout0 fadeout2 fixbrokenchromaupsampling fixluminance fliphorizontal flipvertical frameevaluate freezeframe gaussresize generalconvolution getchannel getchannels getmtmode getparity grayscale greyscale histogram horizontalreduceby2 imagereader imagesource imagewriter info interleave internalcache internalcachemt invert killaudio killvideo lanczos4resize lanczosresize layer letterbox levels limiter loop mask maskhs max merge mergeargb mergechannels mergechroma mergeluma mergergb messageclip min mixaudio monotostereo normalize null opendmlsource overlay peculiarblend pointresize pulldown reduceby2 resampleaudio resetmask reverse rgbadjust scriptclip segmentedavisource segmenteddirectshowsource selecteven selectevery selectodd selectrangeevery separatefields setmtmode sharpen showalpha showblue showfiveversions showframenumber showgreen showred showsmpte showtime sincresize skewrows spatialsoften spline16resize spline36resize spline64resize ssrc stackhorizontal stackvertical subtitle subtract supereq swapfields swapuv temporalsoften timestretch tone trim turn180 turnleft turnright tweak unalignedsplice utoy utoy8 version verticalreduceby2 vtoy vtoy8 wavsource weave writefile writefileend writefileif writefilestart ytouv"
"addgrain addgrainc agc_hdragc analyzelogo animeivtc asharp audiograph autocrop autoyuy2 avsrecursion awarpsharp bassaudiosource bicublinresize bifrost binarize blendfields blindpp blockbuster bordercontrol cfielddiff cframediff chromashift cnr2 colormatrix combmask contra convolution3d convolution3dyv12 dctfilter ddcc deblendlogo deblock deblock_qed decimate decomb dedup deen deflate degrainmedian depan depanestimate depaninterleave depanscenes depanstabilize descratch despot dfttest dgbob dgsource directshowsource distancefunction dss2 dup dupmc edeen edgemask ediupsizer eedi2 eedi3 eedi3_rpow2 expand faerydust fastbicubicresize fastbilinearresize fastediupsizer dedgemask fdecimate ffaudiosource ffdshow ffindex ffmpegsource ffmpegsource2 fft3dfilter fft3dgpu ffvideosource fielddeinterlace fielddiff fillmargins fity2uv fity2u fity2v fitu2y fitv2y fluxsmooth fluxsmoothst fluxsmootht framediff framenumber frfun3b frfun7 gicocu golddust gradfun2db grapesmoother greedyhma grid guavacomb hqdn3d hybridfupp hysteresymask ibob improvesceneswitch inflate inpand inpaintlogo interframe interlacedresize interlacedwarpedresize interleaved2planar iscombed iscombedt iscombedtivtc kerneldeint leakkernelbob leakkerneldeint limitedsharpen limitedsharpenfaster logic lsfmod lumafilter lumayv12 manalyse maskeddeinterlace maskedmerge maskedmix mblockfps mcompensate mctemporaldenoise mctemporaldenoisepp mdegrain1 mdegrain2 mdegrain3 mdepan medianblur mergehints mflow mflowblur mflowfps mflowinter minblur mipsmooth mmask moderatesharpen monitorfilter motionmask mpasource mpeg2source mrecalculate mscdetection msharpen mshow msmooth msu_fieldshiftfixer msu_frc msuper mt mt_adddiff mt_average mt_binarize mt_circle mt_clamp mt_convolution mt_deflate mt_diamond mt_edge mt_ellipse mt_expand mt_freeellipse mt_freelosange mt_freerectangle mt_hysteresis mt_infix mt_inflate mt_inpand mt_invert mt_logic mt_losange mt_lut mt_lutf mt_luts mt_lutspa mt_lutsx mt_lutxy mt_lutxyz mt_makediff mt_mappedblur mt_merge mt_motion mt_polish mt_rectangle mt_square mti mtsource multidecimate mvanalyse mvblockfps mvchangecompensate mvcompensate mvdegrain1 mvdegrain2 mvdegrain3 mvdenoise mvdepan mvflow mvflowblur mvflowfps mvflowfps2 mvflowinter mvincrease mvmask mvrecalculate mvscdetection mvshow nicac3source nicdtssource niclpcmsource nicmpasource nicmpg123source nnedi nnedi2 nnedi2_rpow2 nnedi3 nnedi3_rpow2 nomosmooth overlaymask peachsmoother pixiedust planar2interleaved qtgmc qtinput rawavsource rawsource reduceflicker reinterpolate411 removedirt removedust removegrain removegrainhd removetemporalgrain repair requestlinear reversefielddominance rgb3dlut rgdeinterlace rgsdeinterlace rgblut rotate sangnom seesaw sharpen2 showchannels showcombedtivtc smartdecimate smartdeinterlace smdegrain smoothdeinterlace smoothuv soothess soxfilter spacedust sshiq ssim ssiq stmedianfilter t3dlut tanisotropic tbilateral tcanny tcomb tcombmask tcpserver tcpsource tdecimate tdeint tedgemask telecide temporalcleaner temporalrepair temporalsmoother tfieldblank tfm tisophote tivtc tmaskblank tmaskedmerge tmaskedmerge3 tmm tmonitor tnlmeans tomsmocomp toon textsub ttempsmooth ttempsmoothf tunsharp unblock uncomb undot unfilter unsharpmask vaguedenoiser variableblur verticalcleaner videoscope vinverse vobsub vqmcalc warpedresize warpsharp xsharpen yadif yadifmod yuy2lut yv12convolution yv12interlacedreduceby2 yv12interlacedselecttopfields yv12layer yv12lut yv12lutxy yv12substract yv12torgb24 yv12toyuy2"
"abs apply assert bool ceil chr clip continueddenominator continuednumerator cos default defined eval averagechromau averagechromav averageluma chromaudifference chromavdifference lumadifference exist exp findstr float floor frac hexvalue import int isbool isclip isfloat isint isstring lcase leftstr load_stdcall_plugin loadcplugin loadplugin loadvfapiplugin loadvirtualdubplugin log midstr muldiv nop opt_allowfloataudio opt_avipadscanlines opt_dwchannelmask opt_usewaveextensible opt_vdubplanarhack pi pow rand revstr rightstr round scriptdir scriptfile scriptname select setmemorymax setplanarlegacyalignment rgbdifference rgbdifferencefromprevious rgbdifferencetonext udifferencefromprevious udifferencetonext setworkingdir sign sin spline sqrt string strlen time ucase undefined value versionnumber versionstring uplanemax uplanemedian uplanemin uplaneminmaxdifference vdifferencefromprevious vdifferencetonext vplanemax vplanemedian vplanemin vplaneminmaxdifference ydifferencefromprevious ydifferencetonext yplanemax yplanemedian yplanemin yplaneminmaxdifference"
"audiobits audiochannels audiolength audiolengthf audiorate framecount framerate frameratedenominator frameratenumerator getleftchannel getrightchannel hasaudio hasvideo height isaudiofloat isaudioint isfieldbased isframebased isinterleaved isplanar isrgb isrgb24 isrgb32 isyuv isyuy2 isyv12 width"
""
"";
// color text
static SScintillaColors g_rgb_Syntax_avs[] =
{ {} };

//--------------------------------
//---- baanc Language
//--------------------------------
// language
static CString g_str_baanc_language = _T("baanc");
// extentions
static CString g_str_baanc_extention = _T("baanc");
// comment line
static CString g_str_baanc_commentline = _T("|");
// comment start
static CString g_str_baanc_commentStart = _T("");
// comment end
static CString g_str_baanc_commentEnd = _T("");
// keywords
static const char* g_baanc_KeyWords =
"alike all and array as asc at avg base based between boolean both break bset buffer by call case cast chart clear clearunref common const continue count cross current_date current_timestamp date date.num date.to.num debug default delete deleteempty deleteerror desc dim distinct dll dllusage domain double else empty end endcase enddelete enddllusage endfor endfunctionusage endif endselect endupdate endwhile enum_description eq escape exists extern false fatal fetching field first fixed for from full function functionusage ge global goto group gt having hint hints if in include index inner input inrange integer is join label last le leading left like long lt max mb menu message min multibyte ne no nodebug not notransactions nowarnings null on or order ordered outer path pi prepared print prompt question raw real ref reference refers repeat retry return right row rows select selectbind selectdo selectempty selecteos selecterror session set setunref size skip static step sticky stop strict_boolean string subhint sum table text_content then timestamp to trailing trim true union unref until update updateempty updateerror use used void warning warnings when where wherebind whereused while with"
"abort abort.io db.after.delete db.after.insert db.after.update xmlSetData zoom.to$"
"~.is.mandatory"
"after.choice: after.delete: after.display: after.field: after.form: after.group: after.input: after.layout: after.read: after.rewrite: after.skip.delete: after.skip.rewrite: after.skip.write: after.write: after.zoom: before.checks:  before.choice: before.delete: before.display: before.field: before.form: before.group: before.input: before.layout: before.print: before.read: before.rewrite: before.write: before.zoom: check.input: domain.error: init.field: init.form: init.group: on.choice: on.entry: on.exit: on.input: read.view: ref.display: ref.input: selection.filter: when.field.changes:"
"after.~: before.~: choice.~: choice.abort.program: choice.abort.work: choice.add.set: choice.ask.helpinfo: choice.attachments: choice.bms: choice.calculator: choice.calender: choice.cancel.work: choice.change.frm: choice.change.order: choice.cmd.about.baan: choice.cmd.copy: choice.cmd.cut: choice.cmd.options: choice.cmd.paste: choice.cont.process: choice.create.job: choice.current.work: choice.cust.grid: choice.def.find: choice.display.set: choice.dupl.occur: choice.end.program: choice.field.browse: choice.field.help: choice.find.data: choice.first.frm: choice.first.set: choice.first.view: choice.freeze.columns: choice.get.defaults: choice.global.copy: choice.global.delete: choice.glossary: choice.help.index: choice.hide.fields: choice.interrupt: choice.last.frm: choice.last.set: choice.last.view: choice.mark.delete: choice.mark.occur: choice.modify.set: choice.next.frm: choice.next.set: choice.next.view: choice.next.work: choice.prev.frm: choice.prev.set: choice.prev.view: choice.print.data: choice.processes: choice.recover.set: choice.reference: choice.resize.frm: choice.rotate.curr: choice.run.job: choice.save.defaults: choice.select.all: choice.send.data: choice.sendto.desktop: choice.sendto.editor: choice.sendto.mail: choice.sendto.tasklst: choice.start.chart: choice.start.query: choice.start.set: choice.suspend.work: choice.switch.windows: choice.synchronize: choice.text.manager: choice.to.clipboard: choice.unfreeze.colum: choice.update.db: choice.user.0: choice.user.1: choice.user.2: choice.user.3: choice.user.4: choice.user.5: choice.user.6: choice.user.7: choice.user.8: choice.user.9: choice.using.help: choice.zoom:  declaration: detail.~: field.~: footer.~: form.~: functions: group.~: header.~:  main.table.io: on.display.total.line: on.error: zoom.from.~:"
"actual.occ zoomreturn$"
"__file__ z.session"
"^tcyesno. ^tdsls.corg."
"dalnew dalupdate"
"dalnew dalupdate";
// color text
static SScintillaColors g_rgb_Syntax_baanc[] =
{ {} };

//--------------------------------
//---- bash Language
//--------------------------------
// language
static CString g_str_bash_language = _T("bash");
// extentions
static CString g_str_bash_extention = _T("bash");
// comment line
static CString g_str_bash_commentline = _T("#");
// comment start
static CString g_str_bash_commentStart = _T("");
// comment end
static CString g_str_bash_commentEnd = _T("");
// keywords
static const char* g_bash_KeyWords =
"7z adduser alias apt-get ar as asa autoconf automake awk banner base64 basename bash bc bdiff blkid break bsdcpio bsdtar bunzip2 bzcmp bzdiff bzegrep bzfgrep bzgrep bzip2 bzip2recover bzless bzmore c++ cal calendar case cat cc cd cfdisk chattr chgrp chmod chown chroot chvt cksum clang clang++ clear cmp col column comm compgen compress continue convert cp cpio crontab crypt csplit ctags curl cut date dc dd deallocvt declare deluser depmod deroff df dialog diff diff3 dig dircmp dirname disown dmesg do done dpkg dpkg-deb du echo ed egrep elif else env esac eval ex exec exit expand export expr fakeroot false fc fdisk ffmpeg fgrep fi file find flex flock fmt fold for fsck function functions fuser fusermount g++ gas gawk gcc gdb genisoimage getconf getopt getopts git gpg gpgsplit gpgv grep gres groff groups gunzip gzexe hash hd head help hexdump hg history httpd iconv id if ifconfig ifdown ifquery ifup in insmod integer inxi ip ip6tables ip6tables-save ip6tables-restore iptables iptables-save iptables-restore ip jobs join kill killall killall5 lc ld ldd let lex line ln local logname look ls lsattr lsb_release lsblk lscpu lshw lslocks lsmod lsusb lzcmp lzegrep lzfgrep lzgrep lzless lzma lzmainfo lzmore m4 mail mailx make man mkdir mkfifo mkswap mktemp modinfo modprobe mogrify more mount msgfmt mt mv nameif nasm nc ndisasm netcat newgrp nl nm nohup ntps objdump od openssl p7zip pacman passwd paste patch pathchk pax pcat pcregrep pcretest perl pg ping ping6 pivot_root poweroff pr print printf ps pwd python python2 python3 ranlib read readlink readonly reboot reset return rev rm rmdir rmmod rpm rsync sed select service set sh sha1sum sha224sum sha256sum sha3sum sha512sum shift shred shuf shutdown size sleep sort spell split start stop strings strip stty su sudo sum suspend switch_root sync systemctl tac tail tar tee test then time times touch tr trap troff true tsort tty type typeset ulimit umask umount unalias uname uncompress unexpand uniq unlink unlzma unset until unzip unzipsfx useradd userdel uudecode uuencode vi vim wait wc wget whence which while who wpaste wstart xargs xdotool xxd xz xzcat xzcmp xzdiff xzfgrep xzgrep xzless xzmore yes yum zcat zcmp zdiff zegrep zfgrep zforce zgrep zless zmore znew zsh"
"7z adduser alias apt-get ar as asa autoconf automake awk banner base64 basename bash bc bdiff blkid break bsdcpio bsdtar bunzip2 bzcmp bzdiff bzegrep bzfgrep bzgrep bzip2 bzip2recover bzless bzmore c++ cal calendar case cat cc cd cfdisk chattr chgrp chmod chown chroot chvt cksum clang clang++ clear cmp col column comm compgen compress continue convert cp cpio crontab crypt csplit ctags curl cut date dc dd deallocvt declare deluser depmod deroff df dialog diff diff3 dig dircmp dirname disown dmesg do done dpkg dpkg-deb du echo ed egrep elif else env esac eval ex exec exit expand export expr fakeroot false fc fdisk ffmpeg fgrep fi file find flex flock fmt fold for fsck function functions fuser fusermount g++ gas gawk gcc gdb genisoimage getconf getopt getopts git gpg gpgsplit gpgv grep gres groff groups gunzip gzexe hash hd head help hexdump hg history httpd iconv id if ifconfig ifdown ifquery ifup in insmod integer inxi ip ip6tables ip6tables-save ip6tables-restore iptables iptables-save iptables-restore ip jobs join kill killall killall5 lc ld ldd let lex line ln local logname look ls lsattr lsb_release lsblk lscpu lshw lslocks lsmod lsusb lzcmp lzegrep lzfgrep lzgrep lzless lzma lzmainfo lzmore m4 mail mailx make man mkdir mkfifo mkswap mktemp modinfo modprobe mogrify more mount msgfmt mt mv nameif nasm nc ndisasm netcat newgrp nl nm nohup ntps objdump od openssl p7zip pacman passwd paste patch pathchk pax pcat pcregrep pcretest perl pg ping ping6 pivot_root poweroff pr print printf ps pwd python python2 python3 ranlib read readlink readonly reboot reset return rev rm rmdir rmmod rpm rsync sed select service set sh sha1sum sha224sum sha256sum sha3sum sha512sum shift shred shuf shutdown size sleep sort spell split start stop strings strip stty su sudo sum suspend switch_root sync systemctl tac tail tar tee test then time times touch tr trap troff true tsort tty type typeset ulimit umask umount unalias uname uncompress unexpand uniq unlink unlzma unset until unzip unzipsfx useradd userdel uudecode uuencode vi vim wait wc wget whence which while who wpaste wstart xargs xdotool xxd xz xzcat xzcmp xzdiff xzfgrep xzgrep xzless xzmore yes yum zcat zcmp zdiff zegrep zfgrep zforce zgrep zless zmore znew zsh";
// color text
static SScintillaColors g_rgb_Syntax_bash[] =
{ {} };

//--------------------------------
//---- batch Language
//--------------------------------
// language
static CString g_str_batch_language = _T("batch");
// extentions
static CString g_str_batch_extention = _T("batch");
// comment line
static CString g_str_batch_commentline = _T("REM");
// comment start
static CString g_str_batch_commentStart = _T("");
// comment end
static CString g_str_batch_commentEnd = _T("");
// keywords
static const char* g_batch_KeyWords =
"assoc aux break call cd chcp chdir choice cls cmdextversion color com com1 com2 com3 com4 con copy country ctty date defined del dir do dpath echo else endlocal erase errorlevel exist exit for ftype goto if in loadfix loadhigh lpt lpt1 lpt2 lpt3 lpt4 md mkdir move not nul path pause popd prn prompt pushd rd rem ren rename rmdir set setlocal shift start time title type ver verify vol"
"assoc aux break call cd chcp chdir choice cls cmdextversion color com com1 com2 com3 com4 con copy country ctty date defined del dir do dpath echo else endlocal erase errorlevel exist exit for ftype goto if in loadfix loadhigh lpt lpt1 lpt2 lpt3 lpt4 md mkdir move not nul path pause popd prn prompt pushd rd rem ren rename rmdir set setlocal shift start time title type ver verify vol";
// color text
static SScintillaColors g_rgb_Syntax_batch[] =
{ {} };

//--------------------------------
//---- blitzbasic Language
//--------------------------------
// language
static CString g_str_blitzbasic_language = _T("blitzbasic");
// extentions
static CString g_str_blitzbasic_extention = _T("blitzbasic");
// comment line
static CString g_str_blitzbasic_commentline = _T("");
// comment start
static CString g_str_blitzbasic_commentStart = _T("");
// comment end
static CString g_str_blitzbasic_commentEnd = _T("");
// keywords
static const char* g_blitzbasic_KeyWords =
"abs accepttcpstream acos after and apptitle asc asin atan atan2 automidhandle autosuspend availvidmem backbuffer banksize before bin calldll case ceil changedir channelpan channelpitch channelplaying channelvolume chr closedir closefile closemovie closetcpserver closetcpstream closeudpstream cls clscolor color colorblue colorgreen colorred commandline const copybank copyfile copyimage copypixel copypixelfast copyrect copystream cos countgfxdrivers countgfxmodes counthostips createbank createdir createimage createnetplayer createprocess createtcpserver createtimer createudpstream currentdate currentdir currenttime data debuglog default delay delete deletedir deletefile deletenetplayer desktopbuffer dim dottedip drawblock drawblockrect drawimage drawimagerect drawmovie each else else if elseif end end function end if end select end type endgraphics endif eof execfile exit exp false field filepos filesize filetype first flip float floor flushjoy flushkeys flushmouse fontheight fontname fontsize fontstyle fontwidth for forever freebank freefont freeimage freesound freetimer frontbuffer function gammablue gammagreen gammared getcolor getenv getkey getmouse gfxdrivername gfxmodedepth gfxmodeexists gfxmodeformat gfxmodeheight gfxmodewidth global gosub goto grabimage graphics graphicsbuffer graphicsdepth graphicsformat graphicsheight graphicswidth handleimage hex hidepointer hostip hostnetgame if imagebuffer imageheight imagerectcollide imagerectoverlap imagescollide imagesoverlap imagewidth imagexhandle imageyhandle include input insert instr int joinnetgame joydown joyhat joyhit joypitch joyroll joytype joyu joyudir joyv joyvdir joyx joyxdir joyy joyyaw joyydir joyz joyzdir keydown keyhit keywait last left len line loadanimimage loadbuffer loadfont loadimage loadsound local lockbuffer lockedformat lockedpitch lockedpixels log log10 loopsound lower lset maskimage mid midhandle millisecs mod morefiles mousedown mousehit mousex mousexspeed mousey mouseyspeed mousez mousezspeed movemouse movieheight movieplaying moviewidth netmsgdata netmsgfrom netmsgto netmsgtype netplayerlocal netplayername new next nextfile not null openfile openmovie opentcpstream or origin oval pausechannel pausetimer peekbyte peekfloat peekint peekshort pi playcdtrack playmusic playsound plot pokebyte pokefloat pokeint pokeshort print queryobject rand read readavail readbyte readbytes readdir readfile readfloat readint readline readpixel readpixelfast readshort readstring rect rectsoverlap recvnetmsg recvudpmsg repeat replace resettimer resizebank resizeimage restore resumechannel resumetimer return right rnd rndseed rotateimage rset runtimeerror sar savebuffer saveimage scaleimage scanline seedrnd seekfile select sendnetmsg sendudpmsg setbuffer setenv setfont setgamma setgfxdriver sgn shl showpointer shr sin soundpan soundpitch soundvolume sqr startnetgame step stop stopchannel stopnetgame str string stringheight stringwidth systemproperty tan tcpstreamip tcpstreamport tcptimeouts text tformfilter tformimage then tileblock tileimage timerticks to totalvidmem trim true type udpmsgip udpmsgport udpstreamip udpstreamport udptimeouts unlockbuffer until updategamma upper viewport vwait waitkey waitmouse waittimer wend while write writebyte writebytes writefile writefloat writeint writeline writepixel writepixelfast writeshort writestring xor"
""
""
""
"";
// color text
static SScintillaColors g_rgb_Syntax_blitzbasic[] =
{ {} };

//--------------------------------
//---- c Language
//--------------------------------
// language
static CString g_str_c_language = _T("c");
// extentions
static CString g_str_c_extention = _T("c");
// comment line
static CString g_str_c_commentline = _T("//");
// comment start
static CString g_str_c_commentStart = _T("/*");
// comment end
static CString g_str_c_commentEnd = _T("*/");
// keywords
static const char* g_c_KeyWords =
"if else switch case default break goto return for while do continue typedef sizeof offsetof alignof _Alignof _Generic _Static_assert and and_eq bitand bitor compl not not_eq or or_eq xor xor_eq NULL"
"void struct union enum char short int long double float signed unsigned const static extern auto register volatile restrict _Atomic bool _Bool complex _Complex imaginary _Imaginary inline noreturn _Noreturn alignas _Alignas thread_local _Thread_local uint8_t uint16_t uint32_t uint64_t int8_t int16_t int32_t int64_t uint_least8_t uint_least16_t uint_least32_t uint_least64_t int_least8_t int_least16_t int_least32_t int_least64_t uint_fast8_t uint_fast16_t uint_fast32_t uint_fast64_t int_fast8_t int_fast16_t int_fast32_t int_fast64_t uintptr_t intptr_t uintmax_t intmax_t ptrdiff_t max_align_t div_t ldiv_t lldiv_t imaxdiv_t size_t time_t clock_t wchar_t char16_t char32_t sig_atomic_t FILE"
"void struct union enum char short int long double float signed unsigned const static extern auto register volatile restrict _Atomic bool _Bool complex _Complex imaginary _Imaginary inline noreturn _Noreturn alignas _Alignas thread_local _Thread_local uint8_t uint16_t uint32_t uint64_t int8_t int16_t int32_t int64_t uint_least8_t uint_least16_t uint_least32_t uint_least64_t int_least8_t int_least16_t int_least32_t int_least64_t uint_fast8_t uint_fast16_t uint_fast32_t uint_fast64_t int_fast8_t int_fast16_t int_fast32_t int_fast64_t uintptr_t intptr_t uintmax_t intmax_t ptrdiff_t max_align_t div_t ldiv_t lldiv_t imaxdiv_t size_t time_t clock_t wchar_t char16_t char32_t sig_atomic_t FILE";
// color text
static SScintillaColors g_rgb_Syntax_c[] =
{ {} };

//--------------------------------
//---- caml Language
//--------------------------------
// language
static CString g_str_caml_language = _T("caml");
// extentions
static CString g_str_caml_extention = _T("caml");
// comment line
static CString g_str_caml_commentline = _T("");
// comment start
static CString g_str_caml_commentStart = _T("(*");
// comment end
static CString g_str_caml_commentEnd = _T("*)");
// keywords
static const char* g_caml_KeyWords =
"and as assert asr begin class constraint do done downto else end exception external false for fun function functor if in include inherit initializer land lazy let lor lsl lsr lxor match method mod module mutable new object of open or private rec sig struct then to true try type val virtual when while with"
"option Some None ignore ref lnot succ pred"
"array bool char float int list string unit"
"array bool char float int list string unit";
// color text
static SScintillaColors g_rgb_Syntax_caml[] =
{ {} };

//--------------------------------
//---- cmake Language
//--------------------------------
// language
static CString g_str_cmake_language = _T("cmake");
// extentions
static CString g_str_cmake_extention = _T("cmake");
// comment line
static CString g_str_cmake_commentline = _T("#");
// comment start
static CString g_str_cmake_commentStart = _T("");
// comment end
static CString g_str_cmake_commentEnd = _T("");
// keywords
static const char* g_cmake_KeyWords =
"add_custom_command add_compile_definitions add_compile_options add_custom_command add_custom_target add_definitions add_dependencies add_executable add_library add_link_options add_subdirectory add_test aux_source_directory build_command build_name cmake_minimum_required configure_file create_test_sourcelist else elseif enable_language enable_testing endforeach endfunction endif endmacro endwhile exec_program execute_process export export_library_dependencies file find_file find_library find_package find_path find_program fltk_wrap_ui foreach function get_cmake_property get_directory_property get_filename_component get_source_file_property get_target_property get_test_property if include include_directories include_external_msproject include_regular_expression install install_files install_programs install_targets link_directories link_libraries list load_cache load_command macro make_directory mark_as_advanced math message option output_required_files project qt_wrap_cpp qt_wrap_ui remove remove_definitions separate_arguments set set_directory_properties set_source_files_properties set_target_properties set_tests_properties site_name source_group string subdir_depends subdirs target_compile_definitions target_compile_features target_compile_options target_include_directories target_link_directories target_link_libraries target_link_options target_sources try_compile try_run use_mangled_mesa utility_source variable_requires vtk_make_instantiator vtk_wrap_java vtk_wrap_python vtk_wrap_tcl while write_file"
"ABSOLUTE ABSTRACT ADDITIONAL_MAKE_CLEAN_FILES ALL AND APPEND ARGS ASCII BEFORE CACHE CACHE_VARIABLES CLEAR COMMAND COMMANDS COMMAND_NAME COMMENT COMPARE COMPILE_FLAGS COPYONLY DEFINED DEFINE_SYMBOL DEPENDS DOC EQUAL ESCAPE_QUOTES EXCLUDE EXCLUDE_FROM_ALL EXISTS EXPORT_MACRO EXT EXTRA_INCLUDE FATAL_ERROR FILE FILES FORCE FUNCTION GENERATED GLOB GLOB_RECURSE GREATER GROUP_SIZE HEADER_FILE_ONLY HEADER_LOCATION IMMEDIATE INCLUDES INCLUDE_DIRECTORIES INCLUDE_INTERNALS INCLUDE_REGULAR_EXPRESSION LESS LINK_DIRECTORIES LINK_FLAGS LOCATION MACOSX_BUNDLE MACROS MAIN_DEPENDENCY MAKE_DIRECTORY MATCH MATCHALL MATCHES MODULE NAME NAME_WE NOT NOTEQUAL NO_SYSTEM_PATH OBJECT_DEPENDS OPTIONAL OR OUTPUT OUTPUT_VARIABLE PATH PATHS POST_BUILD POST_INSTALL_SCRIPT PREFIX PREORDER PRE_BUILD PRE_INSTALL_SCRIPT PRE_LINK PROGRAM PROGRAM_ARGS PROPERTIES QUIET RANGE READ REGEX REGULAR_EXPRESSION REPLACE REQUIRED RETURN_VALUE RUNTIME_DIRECTORY SEND_ERROR SHARED SOURCES STATIC STATUS STREQUAL STRGREATER STRLESS SUFFIX TARGET TOLOWER TOUPPER VAR VARIABLES VERSION WIN32 WRAP_EXCLUDE WRITE APPLE MINGW MSYS CYGWIN BORLAND WATCOM MSVC MSVC_IDE MSVC60 MSVC70 MSVC71 MSVC80 CMAKE_COMPILER_2005 OFF ON"
""
"";
// color text
static SScintillaColors g_rgb_Syntax_cmake[] =
{ {} };

//--------------------------------
//---- cobol Language
//--------------------------------
// language
static CString g_str_cobol_language = _T("cobol");
// extentions
static CString g_str_cobol_extention = _T("cobol");
// comment line
static CString g_str_cobol_commentline = _T("*>");
// comment start
static CString g_str_cobol_commentStart = _T("");
// comment end
static CString g_str_cobol_commentEnd = _T("");
// keywords
static const char* g_cobol_KeyWords =
"configuration data declaratives division environment file file-control function function-id i-o i-o-control identification input input-output linkage local-storage output procedure program program-id screen section special-names working-storage exec end-exec"
"accept add allocate alter call cancel close commit compute continue delete destroy disable display divide enable entry evaluate also when exit free generate go to goback if else initialize initiate inquire invoke inspect merge modify move multiply next sentence open perform purge raise read ready receive release reset resume return rewrite rollback search send set sort start stop string subtract suppress terminate transform unlock unstring use validate write   end-accept end-add end-call end-compute end-delete end-display end-divide end-evaluate end-if end-multiply end-of-page end-perform end-read end-receive end-return end-rewrite end-search end-start end-string end-subtract end-unstring end-write   copy replace   abs acos annuity asin atan boolean-of-integer byte-length char char-national combined-datetime concatenate cos currency-symbol current-date date-of-integer date-to-yyyymmdd day-of-integer day-to-yyyyddd display-of e exception-file exception-file-n exception-location exception-location-n exception-statement exception-status exp exp10 factorial formatted-current-date formatted-date formatted-datetime formatted-time fraction-part highest-algebraic integer integer-of-boolean integer-of-date integer-of-day integer-of-formatted-date integer-part length length-an locale-compare locale-date locale-time locale-time-from-seconds log log10 lower-case lowest-algebraic max mean median midrange min mod module-caller-id module-date module-formatted-date module-id module-path module-source module-time monetary-decimal-point monetary-thousands-separator national-of numeric-decimal-point numeric-thousands-separator numval numval-c numval-f ord ord-max ord-min pi present-value random range rem reverse seconds-from-formatted-time seconds-past-midnight sign sin sqrt standard-compare standard-deviation stored-char-length substitute substitute-case sum tan test-date-yyyymmdd test-day-yyyyddd test-formatted-datetime test-numval test-numval-c test-numval-f trim upper-case variance when-compiled year-to-yyyy"
"high-value high-values low-value low-values space spaces quote quotes zero zeroes zeros  author date-compiled date-modified date-written installation remarks security   cob-crt-status debug-item debug-line debug-name debug-sub-1 debug-sub-2 debug-sub-3 debug-contents number-of-call-parameters return-code return-code-unsigned sort-return  tally dialect-all jnienvptr json-code linage-counter shift-in shift-out sort-control sort-core-size sort-file-size sort-message sort-mode-size  xml-code xml-event xml-information xml-namespace xml-namespace-prefix xml-nnamespace xml-nnamespace-prefix xml-ntext xml-text  sysin sysipt stdin sysout syslist syslst stdout print printer printer-1 syserr stderr console c01 c02 c03 c04 c05 c06 c07 c08 c09 c10 c11 c12 csp formfeed call-convention  switch-0 switch-1 switch-2 switch-3 switch-4 switch-5 switch-6 switch-7 switch-8 switch-9 switch-10 switch-11 switch-12 switch-13 switch-14 switch-15 switch-16 switch-17 switch-18  switch-19 switch-20 switch-21 switch-22 switch-23 switch-24 switch-25 switch-26 switch-27 switch-28 switch-29 switch-30 switch-31 switch-32 switch-33 switch-34 switch-35 switch-36  upsi-0 upsi-1 upsi-2 upsi-3 upsi-4 upsi-5 upsi-6 upsi-7  access active-class address advancing after aligned all alphabet alphabetic alphabetic-lower alphabetic-upper alphanumeric alphanumeric-edited alternate and any anycase are area areas as ascending assign at automatic  b-and b-not b-or b-xor based before binary binary-char binary-double binary-long binary-sequential binary-short bit blank block boolean bottom by  cd cf ch character characters class class-id clock-units code-set col collating cols column columns comma common communication comp comp-3 comp-5 computational computational-3 computational-5 condition constant contains content control controls converting corr corresponding count crt currency cursor  data-pointer date day day-of-week de debugging decimal-point default delimited delimiter depending descending destination detail down duplicates dynamic ec egi emi end enter eo eop equal equals error esi every exception exception-object exclusive extend external  factory false farthest-from-zero fd filler final first float-binary-128 float-binary-32 float-binary-64 float-decimal-16 float-decimal-34 float-extended float-infinity float-long float-not-a-number-quiet float-not-a-number-signaling float-short footing for format from function-pointer  get giving global greater group group-usage heading in in-arithmetic-range index indexed indicate inherits initial initialized interface interface-id into invalid is just justified key label last leading left less limit limits linage line line-counter line-sequential lines locale lock  manual message method method-id minus mode modules multiple national national-edited native nearest-to-zero negative negative-infinity nested no not null number numbers numeric numeric-edited object object-computer object-reference occurs of off omitted on only optional options or order organization other overflow override  packed-decimal padding page page-counter pf ph physical pic picture plus pointer position positive positive-infinity present previous printing procedures proceed program-pointer property prototype queue  raising rd record records redefines reel reference references relative remainder removal renames replacing report reporting reports repository rerun reserve retry returning reversed rewind rf rh right rounded run  same sd segment segment-limit select self separate sequence sequential sharing signed size sort-merge source source-computer sources standard standard-1 standard-2 status step sub-queue-1 sub-queue-2 sub-queue-3 super symbolic sync synchronized system-default  table tallying terminal test text than then through thru time times top trailing true type typedef unit universal unsigned until up upon usage user-default using val-status valid validate-status value values varying with words  arithmetic attribute auto away-from-zero background-color bell binary-c-long binary-encoding blink capacity center chaining classification cobol comp-1 comp-4 comp-6 comp-x computational-1 computational-4 computational-6 computational-x cycle  decimal-encoding entry-convention eol eos erase expands float-binary float-decimal float-not-a-number foreground-color forever full high-order-left high-order-right highlight ignoring implements intermediate intrinsic lc_all lc_collate lc_ctype lc_messages lc_monetary lc_numeric lc_time lowlight  memory nearest-away-from-zero nearest-even-intermediate nearest-toward-zero none normal  paragraph prefixed prohibited recursive relation required reverse-video rounding seconds secure short standard-binary standard-decimal statement strong structure symbol tape toward-greater toward-lesser truncation ucs-4 underline utf-16 utf-8 yyyyddd yyyymmdd  3-d apply background background-high background-low bar blob bold box busy cbl clob combo-box dbclob dbcs draw drop grid grip high hot-track hscroll hscroll-pos id imp kanji low num-rows o-fill oostackptr pos prompt public rowid scroll scroll-bar shadow skip1 skip2 skip3 sql  tab track-thumb unbounded variant virtual-width vscroll vscroll-bar vscroll-pos wait width wrap xml"
"high-value high-values low-value low-values space spaces quote quotes zero zeroes zeros  author date-compiled date-modified date-written installation remarks security   cob-crt-status debug-item debug-line debug-name debug-sub-1 debug-sub-2 debug-sub-3 debug-contents number-of-call-parameters return-code return-code-unsigned sort-return  tally dialect-all jnienvptr json-code linage-counter shift-in shift-out sort-control sort-core-size sort-file-size sort-message sort-mode-size  xml-code xml-event xml-information xml-namespace xml-namespace-prefix xml-nnamespace xml-nnamespace-prefix xml-ntext xml-text  sysin sysipt stdin sysout syslist syslst stdout print printer printer-1 syserr stderr console c01 c02 c03 c04 c05 c06 c07 c08 c09 c10 c11 c12 csp formfeed call-convention  switch-0 switch-1 switch-2 switch-3 switch-4 switch-5 switch-6 switch-7 switch-8 switch-9 switch-10 switch-11 switch-12 switch-13 switch-14 switch-15 switch-16 switch-17 switch-18  switch-19 switch-20 switch-21 switch-22 switch-23 switch-24 switch-25 switch-26 switch-27 switch-28 switch-29 switch-30 switch-31 switch-32 switch-33 switch-34 switch-35 switch-36  upsi-0 upsi-1 upsi-2 upsi-3 upsi-4 upsi-5 upsi-6 upsi-7  access active-class address advancing after aligned all alphabet alphabetic alphabetic-lower alphabetic-upper alphanumeric alphanumeric-edited alternate and any anycase are area areas as ascending assign at automatic  b-and b-not b-or b-xor based before binary binary-char binary-double binary-long binary-sequential binary-short bit blank block boolean bottom by  cd cf ch character characters class class-id clock-units code-set col collating cols column columns comma common communication comp comp-3 comp-5 computational computational-3 computational-5 condition constant contains content control controls converting corr corresponding count crt currency cursor  data-pointer date day day-of-week de debugging decimal-point default delimited delimiter depending descending destination detail down duplicates dynamic ec egi emi end enter eo eop equal equals error esi every exception exception-object exclusive extend external  factory false farthest-from-zero fd filler final first float-binary-128 float-binary-32 float-binary-64 float-decimal-16 float-decimal-34 float-extended float-infinity float-long float-not-a-number-quiet float-not-a-number-signaling float-short footing for format from function-pointer  get giving global greater group group-usage heading in in-arithmetic-range index indexed indicate inherits initial initialized interface interface-id into invalid is just justified key label last leading left less limit limits linage line line-counter line-sequential lines locale lock  manual message method method-id minus mode modules multiple national national-edited native nearest-to-zero negative negative-infinity nested no not null number numbers numeric numeric-edited object object-computer object-reference occurs of off omitted on only optional options or order organization other overflow override  packed-decimal padding page page-counter pf ph physical pic picture plus pointer position positive positive-infinity present previous printing procedures proceed program-pointer property prototype queue  raising rd record records redefines reel reference references relative remainder removal renames replacing report reporting reports repository rerun reserve retry returning reversed rewind rf rh right rounded run  same sd segment segment-limit select self separate sequence sequential sharing signed size sort-merge source source-computer sources standard standard-1 standard-2 status step sub-queue-1 sub-queue-2 sub-queue-3 super symbolic sync synchronized system-default  table tallying terminal test text than then through thru time times top trailing true type typedef unit universal unsigned until up upon usage user-default using val-status valid validate-status value values varying with words  arithmetic attribute auto away-from-zero background-color bell binary-c-long binary-encoding blink capacity center chaining classification cobol comp-1 comp-4 comp-6 comp-x computational-1 computational-4 computational-6 computational-x cycle  decimal-encoding entry-convention eol eos erase expands float-binary float-decimal float-not-a-number foreground-color forever full high-order-left high-order-right highlight ignoring implements intermediate intrinsic lc_all lc_collate lc_ctype lc_messages lc_monetary lc_numeric lc_time lowlight  memory nearest-away-from-zero nearest-even-intermediate nearest-toward-zero none normal  paragraph prefixed prohibited recursive relation required reverse-video rounding seconds secure short standard-binary standard-decimal statement strong structure symbol tape toward-greater toward-lesser truncation ucs-4 underline utf-16 utf-8 yyyyddd yyyymmdd  3-d apply background background-high background-low bar blob bold box busy cbl clob combo-box dbclob dbcs draw drop grid grip high hot-track hscroll hscroll-pos id imp kanji low num-rows o-fill oostackptr pos prompt public rowid scroll scroll-bar shadow skip1 skip2 skip3 sql  tab track-thumb unbounded variant virtual-width vscroll vscroll-bar vscroll-pos wait width wrap xml";
// color text
static SScintillaColors g_rgb_Syntax_cobol[] =
{ {} };

//--------------------------------
//---- csound Language
//--------------------------------
// language
static CString g_str_csound_language = _T("csound");
// extentions
static CString g_str_csound_extention = _T("csound");
// comment line
static CString g_str_csound_commentline = _T(";");
// comment start
static CString g_str_csound_commentStart = _T("");
// comment end
static CString g_str_csound_commentEnd = _T("");
// keywords
static const char* g_csound_KeyWords =
"a i db in or zr Add Dec Div Inc Mul Sub abs and cos dam dec div exp fin fof fog inh ino inq ins int inx inz lfo log mac mod mul not out pan pow rms rnd shl sin sqr sub sum tab tan tb0 tb1 tb2 tb3 tb4 tb5 tb6 tb7 tb8 tb9 urd vco xin xor zar zaw zir ziw zkr zkw adsr babo buzz cent clip comb cosh diff divz fini fink fmb3 fof2 fold fout frac ftsr gain goto in32 inch init line maca moog mute nrpn outc  outh outo outq outs outx outz peak port pset pvoc rand seed sinh  sqrt stix tabw tanh tb10 tb11 tb12 tb13 tb14 tb15 tone vadd vco2  vdiv vexp vibr vmap vmul vpow wrap xout xyin zacl zarg zawm ziwm  zkcl zkwm FLbox FLjoy FLrun adsyn ampdb atone birnd bqrez butbp  butbr buthp butlp clear ctrl7 dbamp dconv delay dumpk endin endop  event expon fouti foutk ftgen ftlen gauss gbuzz grain guiro igoto  ihold instr integ kgoto limit linen log10 loopg loopl lpf18 madsr  max_k metro noise nsamp oscil out32 outch outic outkc outq1 outq2  outq3 outq4 outs1 outs2 pareq pitch pluck portk print pvadd randh  randi rbjeq readk reson rezzy rnd31 scans scanu sense space tab_i  table tbvcf tempo timek times tival tonek tonex vaddv vbap4 vbap8  vbapz vcomb vcopy vdecr vdivv veloc vexpv vibes vincr vmult voice  vport vpowv vpvoc vsubv vwrap wgbow xadsr zamod zkmod FLhide FLkeyb  FLknob FLpack FLshow FLtabs FLtext active adsynt alpass areson  atonek atonex bamboo bbcutm bbcuts biquad cabasa cauchy cggoto  cigoto ckgoto clfilt cngoto convle cosinv cpsoct cpspch cpstun  cpuprc cross2 crunch ctrl14 ctrl21 delay1 delayk delayr delayw  deltap denorm diskin dumpk2 dumpk3 dumpk4 envlpx expseg filesr  fiopen fmbell follow foscil foutir ftlen2 ftload ftmorf ftsave  grain2 grain3 harmon hrtfer initc7 interp jitter linenr lineto  linseg locsig loopge loople lorenz loscil lowres lpread lpslot  mandel mandol mclock mdelay midic7 midiin midion mirror moscil  mpulse mrtmsg mxadsr nlfilt noteon notnum ntrpol octave octcps  octpch opcode oscbnk oscil1 oscil3 oscili osciln oscils oscilx  outiat outipb outipc outkat outkpb outkpc pchoct phasor planet  poscil printk prints pvread pvsftr pvsftw random readk2 readk3  readk4 reinit resonk resonr resonx resony resonz reverb rigoto  s16b14 s32b14 sekere sfload sfplay shaker sininv spat3d spdist  spsend strset table3 tablei tablew tabw_i taninv tigoto timout  turnon upsamp vbap16 vcella vco2ft vdel_k vdelay vlimit vmultv  vrandh vrandi wgclar xscans xscanu FLcolor FLcount FLgroup FLlabel  FLpanel FLvalue aftouch ampdbfs ampmidi aresonk balance bexprnd  biquada changed clockon cps2pch cpsmidi cpstmid cpstuni cpsxpch  dbfsamp dcblock deltap3 deltapi deltapn deltapx dispfft display  envlpxr exprand expsega expsegr filelen filter2 flanger fmmetal  fmrhode fmvoice follow2 foscili fprints ftchnls ftloadk ftlptim  ftsavek gogobel granule hilbert initc14 initc21 invalue jitter2  jspline linrand linsegr locsend logbtwo loopseg loscil3 lowresx  lphasor lposcil lpreson lpshold marimba massign midic14 midic21  midichn midion2 midiout moogvcf noteoff nreverb nstrnum octmidi  oscil1i outic14 outipat outkc14 outkpat pcauchy pchbend pchmidi  phaser1 phaser2 pinkish poisson polyaft poscil3 printk2 printks  product pvcross pvsanal pvsinfo pvsynth randomh randomi release  repluck reverb2 rspline rtclock seqtime sfilist sfinstr sfplay3  sfplaym sfplist slider8 sndwarp soundin spat3di spat3dt specsum  streson tableiw tablekt tableng tablera tablewa taninv2 tempest  tlineto transeg trigger trigseq trirand turnoff unirand valpass  vco2ift vdelay3 vdelayk vdelayx vexpseg vibrato vlinseg vlowres  vmirror waveset weibull wgbrass wgflute wgpluck wguide1 wguide2  xtratim zakinit FLbutton FLcolor2 FLprintk FLroller FLscroll  FLsetBox FLsetVal FLslider FLupdate betarand butterbp butterbr  butterhp butterlp chanctrl clockoff convolve cpsmidib ctrlinit  cuserrnd deltapxw distort1 downsamp duserrnd filepeak fmpercfl  fmwurlie fprintks hsboscil lowpass2 lpfreson lpinterp lposcil3  maxalloc midictrl multitap nestedap octmidib oscilikt outvalue  pchmidib powoftwo prealloc pvinterp pvsadsyn pvscross pvsfread  pvsmaska rireturn samphold schedule semitone sensekey setksmps  sfinstr3 sfinstrm sfplay3m sfpreset slider16 slider32 slider64  slider8f soundout specaddm specdiff specdisp specfilt spechist  specptrk specscal spectrum sprintks subinstr svfilter tablegpw  tableikt tablemix tableseg tablewkt tablexkt tb0_init tb1_init  tb2_init tb3_init tb4_init tb5_init tb6_init tb7_init tb8_init  tb9_init tempoval vco2init vdelayxq vdelayxs vdelayxw vecdelay  wgpluck2 wterrain xscanmap zfilter2 FLbutBank FLgetsnap FLpackEnd  FLprintk2 FLsetFont FLsetSize FLsetText FLsetsnap FLslidBnk  FLtabsEnd dripwater eventname ktableseg noteondur osciliktp  oscilikts pgmassign phasorbnk pitchamdf pvbufread readclock  sandpaper scantable schedwhen sfinstr3m sfpassign slider16f  slider32f slider64f sndwarpst soundoutc soundouts tablecopy  tableigpw tableimix tablexseg tb10_init tb11_init tb12_init  tb13_init tb14_init tb15_init timeinstk timeinsts vbap4move  vbap8move vbapzmove vdelayxwq vdelayxws xscansmap FLgroupEnd  FLloadsnap FLpack_end FLpanelEnd FLsavesnap FLsetAlign FLsetColor  FLsetVal_i FLtabs_end filenchnls noteondur2 scanhammer schedkwhen  tableicopy tambourine vbap16move vbaplsinit wgbowedbar FLgroup_end  FLpanel_end FLscrollEnd FLsetColor2 mididefault midinoteoff  sleighbells FLscroll_end subinstrinit FLsetPosition FLsetTextSize  FLsetTextType midinoteoncps midinoteonkey midinoteonoct  midinoteonpch midipitchbend schedwhenname FLsetTextColor  schedkwhenname midicontrolchange midiprogramchange  midipolyaftertouch midichannelaftertouch"
"sr kr ar ksmps nchnls"
""
"";
// color text
static SScintillaColors g_rgb_Syntax_csound[] =
{ {} };

//--------------------------------
//---- coffeescript Language
//--------------------------------
// language
static CString g_str_coffeescript_language = _T("coffeescript");
// extentions
static CString g_str_coffeescript_extention = _T("coffeescript");
// comment line
static CString g_str_coffeescript_commentline = _T("#");
// comment start
static CString g_str_coffeescript_commentStart = _T("");
// comment end
static CString g_str_coffeescript_commentEnd = _T("");
// keywords
static const char* g_coffeescript_KeyWords =
"new instanceof do return break continue throw for while until loop if else unless switch when then in of by typeof delete where try catch finally prototype jQuery case default function var void with const let enum export import native __hasProp __extends __slice __bind __indexOf"
"Object Number Boolean Array String RegExp Function Date Math eval setInterval clearInterval setTimeout clearTimeout isFinite isNaN parseFloat parseInt escape unescape console encodeURI encodeURIComponent decodeURI decodeURIComponent window document navigator location history screen alert prompt process GLOBAL require exports"
"false true yes no on off undefined null NaN Infinity"
"false true yes no on off undefined null NaN Infinity";
// color text
static SScintillaColors g_rgb_Syntax_coffeescript[] =
{ {} };

//--------------------------------
//---- cpp Language
//--------------------------------
// language
static CString g_str_cpp_language = _T("cpp");
// extentions
static CString g_str_cpp_extention = _T("cpp");
// comment line
static CString g_str_cpp_commentline = _T("//");
// comment start
static CString g_str_cpp_commentStart = _T("/*");
// comment end
static CString g_str_cpp_commentEnd = _T("*/");
// keywords
static const char* g_cpp_KeyWords =
"alignof and and_eq bitand bitor break case catch compl const_cast continue default delete do dynamic_cast else false for goto if namespace new not not_eq nullptr operator or or_eq reinterpret_cast return sizeof static_assert static_cast switch this throw true try typedef typeid using while xor xor_eq NULL"
"alignas asm auto bool char char16_t char32_t class clock_t const constexpr decltype double enum explicit export extern final float friend inline int int8_t int16_t int32_t int64_t int_fast8_t int_fast16_t int_fast32_t int_fast64_t intmax_t intptr_t long mutable noexcept override private protected ptrdiff_t public register short signed size_t ssize_t static struct template thread_local time_t typename uint8_t uint16_t uint32_t uint64_t uint_fast8_t uint_fast16_t uint_fast32_t uint_fast64_t uintmax_t uintptr_t union unsigned virtual void volatile wchar_t"
"a addindex addtogroup anchor arg attention author authors b brief bug c callergraph callgraph category cite class code cond copybrief copydetails copydoc copyright date def defgroup deprecated details diafile dir docbookonly dontinclude dot dotfile e else elseif em endcode endcond enddocbookonly enddot endhtmlonly endif endinternal endlatexonly endlink endmanonly endmsc endparblock endrtfonly endsecreflist enduml endverbatim endxmlonly enum example exception extends f$ f[ f] file fn f{ f} headerfile hidecallergraph hidecallgraph hideinitializer htmlinclude htmlonly idlexcept if ifnot image implements include includelineno ingroup interface internal invariant latexinclude latexonly li line link mainpage manonly memberof msc mscfile n name namespace nosubgrouping note overload p package page par paragraph param parblock post pre private privatesection property protected protectedsection protocol public publicsection pure ref refitem related relatedalso relates relatesalso remark remarks result return returns retval rtfonly sa secreflist section see short showinitializer since skip skipline snippet startuml struct subpage subsection subsubsection tableofcontents test throw throws todo tparam typedef union until var verbatim verbinclude version vhdlflow warning weakgroup xmlonly xrefitem"
"a addindex addtogroup anchor arg attention author authors b brief bug c callergraph callgraph category cite class code cond copybrief copydetails copydoc copyright date def defgroup deprecated details diafile dir docbookonly dontinclude dot dotfile e else elseif em endcode endcond enddocbookonly enddot endhtmlonly endif endinternal endlatexonly endlink endmanonly endmsc endparblock endrtfonly endsecreflist enduml endverbatim endxmlonly enum example exception extends f$ f[ f] file fn f{ f} headerfile hidecallergraph hidecallgraph hideinitializer htmlinclude htmlonly idlexcept if ifnot image implements include includelineno ingroup interface internal invariant latexinclude latexonly li line link mainpage manonly memberof msc mscfile n name namespace nosubgrouping note overload p package page par paragraph param parblock post pre private privatesection property protected protectedsection protocol public publicsection pure ref refitem related relatedalso relates relatesalso remark remarks result return returns retval rtfonly sa secreflist section see short showinitializer since skip skipline snippet startuml struct subpage subsection subsubsection tableofcontents test throw throws todo tparam typedef union until var verbatim verbinclude version vhdlflow warning weakgroup xmlonly xrefitem";
// color text
static SScintillaColors g_rgb_Syntax_cpp[] =
{ {} };

//--------------------------------
//---- cs Language
//--------------------------------
// language
static CString g_str_cs_language = _T("cs");
// extentions
static CString g_str_cs_extention = _T("cs");
// comment line
static CString g_str_cs_commentline = _T("//");
// comment start
static CString g_str_cs_commentStart = _T("/*");
// comment end
static CString g_str_cs_commentEnd = _T("*/");
// keywords
static const char* g_cs_KeyWords =
"abstract add alias as ascending async await base break case catch checked continue default delegate descending do dynamic else event explicit extern false finally fixed for foreach from get global goto group if implicit in interface internal into is join let lock namespace new null object operator orderby out override params partial private protected public readonly ref remove return sealed select set sizeof stackalloc switch this throw true try typeof unchecked unsafe using value virtual where while yield"
"bool byte char class const decimal double enum float int long sbyte short static string struct uint ulong ushort var void"
"bool byte char class const decimal double enum float int long sbyte short static string struct uint ulong ushort var void";
// color text
static SScintillaColors g_rgb_Syntax_cs[] =
{ {} };

//--------------------------------
//---- css Language
//--------------------------------
// language
static CString g_str_css_language = _T("css");
// extentions
static CString g_str_css_extention = _T("css");
// comment line
static CString g_str_css_commentline = _T("");
// comment start
static CString g_str_css_commentStart = _T("/*");
// comment end
static CString g_str_css_commentEnd = _T("*/");
// keywords
static const char* g_css_KeyWords =
"-khtml-background-clip -khtml-background-origin -khtml-background-size -khtml-border-bottom-left-radius -khtml-border-bottom-right-radius -khtml-border-radius -khtml-border-top-left-radius -khtml-border-top-right-radius -khtml-opacity -moz-animation -moz-animation-delay -moz-animation-direction -moz-animation-duration -moz-animation-fill-mode -moz-animation-iteration-count -moz-animation-name -moz-animation-play-state -moz-animation-timing-function -moz-appearance -moz-background-clip -moz-background-inline-policy -moz-background-origin -moz-background-size -moz-binding -moz-border-bottom-colors -moz-border-end -moz-border-end-color -moz-border-end-style -moz-border-end-width -moz-border-image -moz-border-left-colors -moz-border-radius -moz-border-radius-bottomleft -moz-border-radius-bottomright -moz-border-radius-topleft -moz-border-radius-topright -moz-border-right-colors -moz-border-start -moz-border-start-color -moz-border-start-style -moz-border-start-width -moz-border-top-colors -moz-box-align -moz-box-direction -moz-box-flex -moz-box-flex-group -moz-box-flexgroup -moz-box-ordinal-group -moz-box-orient -moz-box-pack -moz-box-shadow -moz-box-sizing -moz-column-count -moz-column-gap -moz-column-rule -moz-column-rule-color -moz-column-rule-style -moz-column-rule-width -moz-column-width -moz-context-properties -moz-float-edge -moz-force-broken-image-icon -moz-image-region -moz-linear-gradient -moz-margin-end -moz-margin-start -moz-opacity -moz-outline -moz-outline-color -moz-outline-offset -moz-outline-radius -moz-outline-radius-bottomleft -moz-outline-radius-bottomright -moz-outline-radius-topleft -moz-outline-radius-topright -moz-outline-style -moz-outline-width -moz-padding-end -moz-padding-start -moz-radial-gradient -moz-stack-sizing -moz-text-decoration-color -moz-text-decoration-line -moz-text-decoration-style -moz-transform -moz-transform-origin -moz-transition -moz-transition-delay -moz-transition-duration -moz-transition-property -moz-transition-timing-function -moz-user-focus -moz-user-input -moz-user-modify -moz-user-select -moz-window-shadow -ms-filter -ms-transform -ms-transform-origin -o-transform -webkit-animation -webkit-animation-delay -webkit-animation-direction -webkit-animation-duration -webkit-animation-fill-mode -webkit-animation-iteration-count -webkit-animation-name -webkit-animation-play-state -webkit-animation-timing-function -webkit-appearance -webkit-backface-visibility -webkit-background-clip -webkit-background-composite -webkit-background-origin -webkit-background-size -webkit-border-bottom-left-radius -webkit-border-bottom-right-radius -webkit-border-horizontal-spacing -webkit-border-image -webkit-border-radius -webkit-border-top-left-radius -webkit-border-top-right-radius -webkit-border-vertical-spacing -webkit-box-align -webkit-box-direction -webkit-box-flex -webkit-box-flex-group -webkit-box-lines -webkit-box-ordinal-group -webkit-box-orient -webkit-box-pack -webkit-box-reflect -webkit-box-shadow -webkit-box-sizing -webkit-column-break-after -webkit-column-break-before -webkit-column-break-inside -webkit-column-count -webkit-column-gap -webkit-column-rule -webkit-column-rule-color -webkit-column-rule-style -webkit-column-rule-width -webkit-column-width -webkit-columns -webkit-dashboard-region -webkit-font-smoothing -webkit-gradient -webkit-line-break -webkit-linear-gradient -webkit-margin-bottom-collapse -webkit-margin-collapse -webkit-margin-start -webkit-margin-top-collapse -webkit-marquee -webkit-marquee-direction -webkit-marquee-increment -webkit-marquee-repetition -webkit-marquee-speed -webkit-marquee-style -webkit-mask -webkit-mask-attachment -webkit-mask-box-image -webkit-mask-clip -webkit-mask-composite -webkit-mask-image -webkit-mask-origin -webkit-mask-position -webkit-mask-position-x -webkit-mask-position-y -webkit-mask-repeat -webkit-mask-size -webkit-nbsp-mode -webkit-padding-start -webkit-perspective -webkit-perspective-origin -webkit-radial-gradient -webkit-rtl-ordering -webkit-tap-highlight-color -webkit-text-fill-color -webkit-text-security -webkit-text-size-adjust -webkit-text-stroke -webkit-text-stroke-color -webkit-text-stroke-width -webkit-touch-callout -webkit-transform -webkit-transform-origin -webkit-transform-origin-x -webkit-transform-origin-y -webkit-transform-origin-z -webkit-transform-style -webkit-transition -webkit-transition-delay -webkit-transition-duration -webkit-transition-property -webkit-transition-timing-function -webkit-user-drag -webkit-user-modify -webkit-user-select align-content align-items align-self alignment-adjust alignment-baseline all animation animation-delay animation-direction animation-duration animation-fill-mode animation-iteration-count animation-name animation-play-state animation-timing-function appearance azimuth backface-visibility background background-attachment background-blend-mode background-break background-clip background-color background-image background-origin background-position background-position-x background-position-y background-repeat background-size baseline-shift binding bleed block-size bookmark-label bookmark-level bookmark-state bookmark-target border border-block border-block-end border-block-start border-bottom border-bottom-color border-bottom-left-radius border-bottom-right-radius border-bottom-style border-bottom-width border-collapse border-color border-image border-image-outset border-image-repeat border-image-slice border-image-source border-image-width border-inline border-inline-end border-inline-end-width border-inline-start border-inline-start-color border-inline-start-style border-inline-start-width border-left border-left-color border-left-style border-left-width border-radius border-right border-right-color border-right-style border-right-width border-spacing border-style border-top border-top-color border-top-left-radius border-top-right-radius border-top-style border-top-width border-width bottom box-align box-decoration-break box-direction box-flex box-flex-group box-lines box-ordinal-group box-orient box-pack box-shadow box-sizing break-after break-before break-inside caption-side caret-color clear clip color color-profile column-count column-fill column-gap column-rule column-rule-color column-rule-style column-rule-width column-span column-width columns content counter-increment counter-reset crop cue cue-after cue-before cursor direction display dominant-baseline drop-initial-after-adjust drop-initial-after-align drop-initial-before-adjust drop-initial-before-align drop-initial-size drop-initial-value elevation empty-cells fill fill-opacity filter fit fit-position flex flex-basis flex-direction flex-flow flex-grow flex-shrink flex-wrap float float-offset font font-effect font-emphasize font-family font-size font-size-adjust font-stretch font-style font-variant font-variant-ligatures font-weight gap grid-area grid-auto-flow grid-auto-rows grid-column grid-column-end grid-column-gap grid-column-start grid-columns grid-gap grid-row grid-row-gap grid-rows grid-template-areas grid-template-columns grid-template-rows hanging-punctuation height hyphenate-after hyphenate-before hyphenate-character hyphenate-lines hyphenate-resource hyphens icon image-orientation image-rendering image-resolution inline-box-align inline-size inset inset-inline-end inset-inline-start justify-content justify-items justify-self left letter-spacing line-height line-stacking line-stacking-ruby line-stacking-shift line-stacking-strategy list-style list-style-image list-style-position list-style-type margin margin-block margin-block-end margin-block-start margin-bottom margin-inline margin-inline-end margin-inline-start margin-left margin-right margin-top mark mark-after mark-before marker-offset marks marquee-direction marquee-play-count marquee-speed marquee-style mask mask-clip mask-image mask-origin mask-position mask-position-x mask-repeat mask-size max-height max-width min-block-size min-height min-inline-size min-width mix-blend-mode move-to nav-down nav-index nav-left nav-right nav-up object-fit opacity order orphans outline outline-color outline-offset outline-style outline-width overflow overflow-anchor overflow-style overflow-wrap overflow-x overflow-y padding padding-block padding-block-end padding-block-start padding-bottom padding-inline padding-inline-end padding-inline-start padding-left padding-right padding-top page page-break-after page-break-before page-break-inside page-policy paint-order pause pause-after pause-before perspective perspective-origin phonemes pitch pitch-range play-during pointer-events position presentation-level punctuation-trim quotes rendering-intent resize rest rest-after rest-before richness right rotation rotation-point ruby-align ruby-overhang ruby-position ruby-span scrollbar-color size speak speak-header speak-numeral speak-punctuation speech-rate stress string-set stroke stroke-dasharray stroke-linejoin stroke-opacity stroke-width tab-size table-layout target target-name target-new target-position text-align text-align-last text-anchor text-decoration text-decoration-color text-decoration-line text-decoration-style text-emphasis text-height text-indent text-justify text-outline text-overflow text-rendering text-shadow text-transform text-wrap top transform transform-origin transform-style transition transition-delay transition-duration transition-property transition-timing-function unicode-bidi user-select vector-effect vertical-align visibility voice-balance voice-duration voice-family voice-pitch voice-pitch-range voice-rate voice-stress voice-volume volume white-space white-space-collapse widows width will-change word-break word-spacing word-wrap z-index"
"active after before check checked disabled empty enabled first first-child first-letter first-line first-of-type focus hover indeterminate invalid lang last-child last-of-type left link not nth-child nth-last-child nth-of-type nth-last-of-type only-child only-of-type optional read-only read-write required right root selection target valid visited"
"active after before check checked disabled empty enabled first first-child first-letter first-line first-of-type focus hover indeterminate invalid lang last-child last-of-type left link not nth-child nth-last-child nth-of-type nth-last-of-type only-child only-of-type optional read-only read-write required right root selection target valid visited";
// color text
static SScintillaColors g_rgb_Syntax_css[] =
{ {} };

//--------------------------------
//---- d Language
//--------------------------------
// language
static CString g_str_d_language = _T("d");
// extentions
static CString g_str_d_extention = _T("d");
// comment line
static CString g_str_d_commentline = _T("//");
// comment start
static CString g_str_d_commentStart = _T("/*");
// comment end
static CString g_str_d_commentEnd = _T("*/");
// keywords
static const char* g_d_KeyWords =
"abstract alias align asm assert auto body bool break byte case cast catch cdouble cent cfloat char class const continue creal dchar debug default delegate delete deprecated do double else enum export extern false final finally float for foreach foreach_reverse function goto idouble if ifloat immutable import in inout int interface invariant ireal is lazy long mixin module new nothrow null out override package pragma private protected public pure real ref return scope shared short static struct super switch synchronized template this throw true try typedef typeid typeof ubyte ucent uint ulong union unittest ushort version void volatile wchar while with"
""
"";
// color text
static SScintillaColors g_rgb_Syntax_d[] =
{ {} };

//--------------------------------
//---- diff Language
//--------------------------------
// language
static CString g_str_diff_language = _T("diff");
// extentions
static CString g_str_diff_extention = _T("diff");
// comment line
static CString g_str_diff_commentline = _T("");
// comment start
static CString g_str_diff_commentStart = _T("");
// comment end
static CString g_str_diff_commentEnd = _T("");
// keywords
static const char* g_diff_KeyWords =
// color text
static SScintillaColors g_rgb_Syntax_diff[] =
{ {} };

//--------------------------------
//---- erlang Language
//--------------------------------
// language
static CString g_str_erlang_language = _T("erlang");
// extentions
static CString g_str_erlang_extention = _T("erlang");
// comment line
static CString g_str_erlang_commentline = _T("%");
// comment start
static CString g_str_erlang_commentStart = _T("");
// comment end
static CString g_str_erlang_commentEnd = _T("");
// keywords
static const char* g_erlang_KeyWords =
"after and andalso band begin bnot bor bsl bsr bxor case catch cond div end fun if let not of or orelse query receive rem try when xor"
"erlang: abs adler32 adler32_combine erlang:append_element apply atom_to_binary atom_to_list binary_to_atom binary_to_existing_atom binary_to_list bitstring_to_list binary_to_term bit_size erlang:bump_reductions byte_size erlang:cancel_timer check_process_code concat_binary crc32 crc32_combine date decode_packet delete_module erlang:demonitor disconnect_node erlang:display element erase erlang:error exit float float_to_list erlang:fun_info erlang:fun_to_list erlang:function_exported garbage_collect get erlang:get_cookie get_keys erlang:get_stacktrace group_leader halt erlang:hash hd erlang:hibernate integer_to_list erlang:integer_to_list iolist_to_binary iolist_size is_alive is_atom is_binary is_bitstring is_boolean erlang:is_builtin is_float is_function is_integer is_list is_number is_pid is_port is_process_alive is_record is_reference is_tuple length link list_to_atom list_to_binary list_to_bitstring list_to_existing_atom list_to_float list_to_integer erlang:list_to_integer list_to_pid list_to_tuple load_module erlang:load_nif erlang:loaded erlang:localtime erlang:localtime_to_universaltime make_ref erlang:make_tuple erlang:max erlang:md5 erlang:md5_final erlang:md5_init erlang:md5_update erlang:memory erlang:min module_loaded erlang:monitor monitor_node node nodes now open_port erlang:phash erlang:phash2 pid_to_list port_close port_command erlang:port_command port_connect port_control erlang:port_call erlang:port_info erlang:port_to_list erlang:ports pre_loaded erlang:process_display process_flag process_info processes purge_module put erlang:raise erlang:read_timer erlang:ref_to_list register registered erlang:resume_process round self erlang:send erlang:send_after erlang:send_nosuspend erlang:set_cookie setelement size spawn spawn_link spawn_monitor spawn_opt split_binary erlang:start_timer statistics erlang:suspend_process erlang:system_flag erlang:system_info erlang:system_monitor erlang:system_profile term_to_binary throw time tl erlang:trace erlang:trace_delivered erlang:trace_info erlang:trace_pattern trunc tuple_size tuple_to_list erlang:universaltime erlang:universaltime_to_localtime unlink unregister whereis erlang:yield"
"-define -else -endif -ifdef -ifndef -include -include_lib -undef"
"-behavior -behaviour -compile -created -created_by -export -file -import -module -modified -modified_by -record -revision -spec -type -vsn"
"@author @clear @copyright @deprecated @doc @docfile @end @equiv @headerfile @hidden @private @reference @see @since @spec @throws @title @todo @TODO @type @version"
"@date @docRoot @link @module @package @section @time @type @version"
"@date @docRoot @link @module @package @section @time @type @version";
// color text
static SScintillaColors g_rgb_Syntax_erlang[] =
{ {} };

//--------------------------------
//---- escript Language
//--------------------------------
// language
static CString g_str_escript_language = _T("escript");
// extentions
static CString g_str_escript_extention = _T("escript");
// comment line
static CString g_str_escript_commentline = _T("");
// comment start
static CString g_str_escript_commentStart = _T("");
// comment end
static CString g_str_escript_commentEnd = _T("");
// keywords
static const char* g_escript_KeyWords =
"basic basicio boats cfgfile file http npc os uo util accessible addmenuitem appendconfigfileelem applyconstraint applydamage applyrawdamage assignrecttoweatherregion append baseskilltorawskill boatfromitem broadcast ban cdbl cint cstr checklineofsight checklosat checkskill consumemana consumereagents consumesubstance createaccount createitematlocation createiteminbackpack createitemininventory createitemincontainer createmenu createmultiatlocation createnpcfromtemplate createrootiteminstoragearea createstoragearea clear_script_profile_counters close damage destroyitem destroymulti destroyrootiteminstoragearea detach disableevents disconnectclient distance disable enableevents enumerateitemsincontainer enumerateonlinecharacters equipfromtemplate equipitem eraseglobalproperty eraseobjproperty enable enabled erase events_waiting exists findconfigelem findobjtypeincontainer findrootiteminstoragearea findstoragearea fclose find fopen fread fseek ftell fwrite gamestat getamount getcommandhelp getconfigint getconfigintkeys getconfigmaxintkey getconfigreal getconfigstring getconfigstringkeys getconfigstringarray getelemproperty getequipmentbylayer getglobalproperty getharvestdifficulty getmapinfo getmenuobjtypes getobjproperty getobjtype getobjtypebyname getproperty getrawskill getregionstring getskill getspelldifficulty getstandingheight getworldheight grantprivilege harvestresource healdamage hex islegalmove insert keys listequippeditems listghostsnearlocation listhostiles listitemsatlocation listitemsnearlocation listitemsnearlocationoftype listmobilesinlineofsight listmobilesnearlocation listmobilesnearlocationex listobjectsinbox loadtusscpfile left len log_profile lower makeboundingbox move moveboat moveboatrelative movecharactertolocation moveitemtocontainer moveitemtolocation move_offline_mobiles openpaperdoll open pack performaction playlightningbolteffect playmovingeffect playmovingeffectxyz playobjectcenteredeffect playsoundeffect playsoundeffectprivate playstationaryeffect printtextabove printtextaboveprivate packages polcore position print queryparam randomdiceroll randomint rawskilltobaseskill readconfigfile readgameclock releaseitem registerforspeechevents registeritemwithboat requestinput reserveitem restartscript resurrect revokeprivilege runawayfrom runawayfromlocation runtoward runtowardlocation reverse run_script_to_completion saveworldstate selectmenuitem2 self sendbuywindow senddialoggump sendevent sendopenspecialcontainer sendpacket sendsellwindow sendskillwindow sendstringastipwindow sendsysmessage sendtextentrygump setanchor setglobalproperty setname setobjproperty setopponent setproperty setrawskill setregionlightlevel setregionweatherlevel setscriptcontroller setwarmode shutdown speakpowerwords splitwords startspelleffect subtractamount systemfindboatbyserial systemfindobjectbyserial say set_critical set_debug set_priority set_priority_divide set_script_option setcmdlevel setdex setint setlightlevel setmaster setname setpassword setstr shrink size sleep sleepms sort spendgold squelch start_script syslog system_rpm target targetcoordinates targetmultiplacement turnawayfrom turnawayfromlocation turnboat turntoward turntowardlocation toggle unloadconfigfile unpack unban unload_scripts upper walkawayfrom walkawayfromlocation walktoward walktowardlocation wander writehtml writehtmlraw wait_for_event movechar_forcelocation moveitem_forcelocation moveitem_normal scriptopt_debug scriptopt_no_interrupt scriptopt_no_runaway te_cancel_disable te_cancel_enable te_style_disable te_style_normal te_style_numerical tgtopt_check_los tgtopt_harmful tgtopt_helpful tgtopt_neutral tgtopt_nocheck_los setprop getprop"
"array const dictionary global local var and default in next not or return to include use enum"
"while for endfor function program endprogram endfunction foreach case else elseif if endcase endenum endforeach endif endwhile"
"while for endfor function program endprogram endfunction foreach case else elseif if endcase endenum endforeach endif endwhile";
// color text
static SScintillaColors g_rgb_Syntax_escript[] =
{ {} };

//--------------------------------
//---- forth Language
//--------------------------------
// language
static CString g_str_forth_language = _T("forth");
// extentions
static CString g_str_forth_extention = _T("forth");
// comment line
static CString g_str_forth_commentline = _T("\");
// comment start
static CString g_str_forth_commentStart = _T("(");
// comment end
static CString g_str_forth_commentEnd = _T(")");
// keywords
static const char* g_forth_KeyWords =
"AGAIN BEGIN CASE DO ELSE ENDCASE ENDOF IF LOOP OF REPEAT THEN UNTIL  WHILE [IF] [ELSE] [THEN] ?DO"
"DUP DROP ROT SWAP OVER @ ! 2@ 2! 2DUP 2DROP 2SWAP 2OVER NIP R@ >R R> 2R@ 2>R 2R> 0= 0< SP@ SP! W@ W! C@ C! < > = <> 0<>SPACE SPACES KEY? KEY THROW CATCH ABORT */ 2* /MOD CELL+ CELLS CHAR+ CHARS MOVE ERASE DABS TITLE HEX DECIMAL HOLD <# # #S #> SIGN D. . U. DUMP (.") >NUMBER ' IMMEDIATE EXIT RECURSE UNLOOP LEAVE HERE ALLOT , C, W, COMPILE, BRANCH, RET, LIT, DLIT, ?BRANCH, ", >MARK >RESOLVE1 <MARK >RESOLVE ALIGN ALIGNED USER-ALLOT USER-HERE HEADER DOES> SMUDGE HIDE :NONAME LAST-WORD ?ERROR ERROR2 FIND1 SFIND SET-CURRENT GET-CURRENT DEFINITIONS GET-ORDER FORTH ONLY SET-ORDER ALSO PREVIOUS VOC-NAME. ORDER LATEST LITERAL 2LITERAL SLITERAL CLITERAL ?LITERAL1 ?SLITERAL1 HEX-LITERAL HEX-SLITERAL ?LITERAL2 ?SLITERAL2 SOURCE EndOfChunk CharAddr PeekChar IsDelimiter GetChar OnDelimiter SkipDelimiters OnNotDelimiter SkipWord SkipUpTo ParseWord NextWord PARSE SKIP CONSOLE-HANDLES REFILL DEPTH ?STACK ?COMP WORD INTERPRET BYE QUIT MAIN1 EVALUATE INCLUDE-FILE INCLUDED >BODY +WORD WORDLIST CLASS! CLASS@ PAR! PAR@ ID. ?IMMEDIATE ?VOC IMMEDIATE VOC WordByAddrWl WordByAddr NLIST WORDS SAVE OPTIONS /notransl ANSI>OEM ACCEPT EMIT CR TYPE EKEY? EKEY EKEY>CHAR EXTERNTASK ERASE-IMPORTS ModuleName ModuleDirName ENVIRONMENT? DROP-EXC-HANDLER SET-EXC-HANDLER HALT ERR CLOSE-FILE CREATE-FILE CREATE-FILE-SHARED OPEN-FILE-SHARED DELETE-FILE FILE-POSITION FILE-SIZE OPEN-FILE READ-FILE REPOSITION-FILE DOS-LINES UNIX-LINES READ-LINE WRITE-FILE RESIZE-FILE WRITE-LINE ALLOCATE FREE RESIZE START SUSPEND RESUME STOP PAUSE MIN MAX TRUE FALSE ASCIIZ> R/O W/O ;CLASS ENDWITH OR AND /STRING SEARCH COMPARE EXPORT ;MODULE SPACE"
"VARIABLE CREATE : VALUE CONSTANT VM: M: var dvar chars OBJ CONSTR: DESTR: CLASS: OBJECT: POINTER USER USER-CREATE USER-VALUE VECT WNDPROC: VOCABULARY -- TASK: CEZ: MODULE:"
"CHAR [CHAR] POSTPONE WITH ['] TO [COMPILE] CHAR ASCII \'"
"REQUIRE WINAPI"
"S" ABORT" Z" " ." C""
"S" ABORT" Z" " ." C"";
// color text
static SScintillaColors g_rgb_Syntax_forth[] =
{ {} };

//--------------------------------
//---- fortran Language
//--------------------------------
// language
static CString g_str_fortran_language = _T("fortran");
// extentions
static CString g_str_fortran_extention = _T("fortran");
// comment line
static CString g_str_fortran_commentline = _T("!");
// comment start
static CString g_str_fortran_commentStart = _T("");
// comment end
static CString g_str_fortran_commentEnd = _T("");
// keywords
static const char* g_fortran_KeyWords =
"access action advance allocatable allocate apostrophe assign assignment associate asynchronous backspace bind blank blockdata call case character class close common complex contains continue critical cycle data deallocate decimal delim default dimension direct do dowhile double doubleprecision else elseif elsewhere encoding end endassociate endblockdata endcritical enddo endenum endfile endforall endfunction endif endinterface endmodule endprocedure endprogram endselect endsubmodule endsubroutine endtype endwhere entry enum eor equivalence err errmsg exist exit external file flush fmt forall form format formatted function go goto id if implicit in include inout integer inquire intent interface intrinsic iomsg iolength iostat kind len logical module name named namelist nextrec nml none nullify number only open opened operator optional out pad parameter pass pause pending pointer pos position precision print private procedure program protected public quote read readwrite real rec recl recursive result return rewind save select selectcase selecttype sequential sign size stat status stop stream submodule subroutine target then to type unformatted unit use value volatile wait where while write"
"abs achar acos acosd adjustl adjustr aimag aimax0 aimin0 aint ajmax0 ajmin0 akmax0 akmin0 all allocated alog alog10 amax0 amax1 amin0 amin1 amod anint any asin asind associated atan atan2 atan2d atand bitest bitl bitlr bitrl bjtest bit_size bktest break btest cabs ccos cdabs cdcos cdexp cdlog cdsin cdsqrt ceiling cexp char clog cmplx conjg cos cosd cosh count cpu_time cshift csin csqrt dabs dacos dacosd dasin dasind datan datan2 datan2d datand date date_and_time dble dcmplx dconjg dcos dcosd dcosh dcotan ddim dexp dfloat dflotk dfloti dflotj digits dim dimag dint dlog dlog10 dmax1 dmin1 dmod dnint dot_product dprod dreal dsign dsin dsind dsinh dsqrt dtan dtand dtanh eoshift epsilon errsns exp exponent float floati floatj floatk floor fraction free huge iabs iachar iand ibclr ibits ibset ichar idate idim idint idnint ieor ifix iiabs iiand iibclr iibits iibset iidim iidint iidnnt iieor iifix iint iior iiqint iiqnnt iishft iishftc iisign ilen imax0 imax1 imin0 imin1 imod index inint inot int int1 int2 int4 int8 iqint iqnint ior ishft ishftc isign isnan izext jiand jibclr jibits jibset jidim jidint jidnnt jieor jifix jint jior jiqint jiqnnt jishft jishftc jisign jmax0 jmax1 jmin0 jmin1 jmod jnint jnot jzext kiabs kiand kibclr kibits kibset kidim kidint kidnnt kieor kifix kind kint kior kishft kishftc kisign kmax0 kmax1 kmin0 kmin1 kmod knint knot kzext lbound leadz len len_trim lenlge lge lgt lle llt log log10 logical lshift malloc matmul max max0 max1 maxexponent maxloc maxval merge min min0 min1 minexponent minloc minval mod modulo mvbits nearest nint not nworkers number_of_processors pack popcnt poppar precision present product radix random random_number random_seed range real repeat reshape rrspacing rshift scale scan secnds selected_int_kind selected_real_kind set_exponent shape sign sin sind sinh size sizeof sngl snglq spacing spread sqrt sum system_clock tan tand tanh tiny transfer transpose trim ubound unpack verify"
"cdabs cdcos cdexp cdlog cdsin cdsqrt cotan cotand dcmplx dconjg dcotan dcotand decode dimag dll_export dll_import doublecomplex dreal dvchk encode find flen flush getarg getcharqq getcl getdat getenv gettim hfix ibchng identifier imag int1 int2 int4 intc intrup invalop iostat_msg isha ishc ishl jfix lacfar locking locnear map nargs nbreak ndperr ndpexc offset ovefl peekcharqq precfill prompt qabs qacos qacosd qasin qasind qatan qatand qatan2 qcmplx qconjg qcos qcosd qcosh qdim qexp qext qextd qfloat qimag qlog qlog10 qmax1 qmin1 qmod qreal qsign qsin qsind qsinh qsqrt qtan qtand qtanh ran rand randu rewrite segment setdat settim system timer undfl unlock union val virtual volatile zabs zcos zexp zlog zsin zsqrt"
"cdabs cdcos cdexp cdlog cdsin cdsqrt cotan cotand dcmplx dconjg dcotan dcotand decode dimag dll_export dll_import doublecomplex dreal dvchk encode find flen flush getarg getcharqq getcl getdat getenv gettim hfix ibchng identifier imag int1 int2 int4 intc intrup invalop iostat_msg isha ishc ishl jfix lacfar locking locnear map nargs nbreak ndperr ndpexc offset ovefl peekcharqq precfill prompt qabs qacos qacosd qasin qasind qatan qatand qatan2 qcmplx qconjg qcos qcosd qcosh qdim qexp qext qextd qfloat qimag qlog qlog10 qmax1 qmin1 qmod qreal qsign qsin qsind qsinh qsqrt qtan qtand qtanh ran rand randu rewrite segment setdat settim system timer undfl unlock union val virtual volatile zabs zcos zexp zlog zsin zsqrt";
// color text
static SScintillaColors g_rgb_Syntax_fortran[] =
{ {} };

//--------------------------------
//---- fortran77 Language
//--------------------------------
// language
static CString g_str_fortran77_language = _T("fortran77");
// extentions
static CString g_str_fortran77_extention = _T("fortran77");
// comment line
static CString g_str_fortran77_commentline = _T("C");
// comment start
static CString g_str_fortran77_commentStart = _T("");
// comment end
static CString g_str_fortran77_commentEnd = _T("");
// keywords
static const char* g_fortran77_KeyWords =
"access action advance allocatable allocate apostrophe assign assignment associate asynchronous backspace bind blank blockdata call case character class close common complex contains continue critical cycle data deallocate decimal delim default dimension direct do dowhile double doubleprecision else elseif elsewhere encoding end endassociate endblockdata endcritical enddo endenum endfile endforall endfunction endif endinterface endmodule endprocedure endprogram endselect endsubmodule endsubroutine endtype endwhere entry enum eor equivalence err errmsg exist exit external file flush fmt forall form format formatted function go goto id if implicit in include inout integer inquire intent interface intrinsic iomsg iolength iostat kind len logical module name named namelist nextrec nml none nullify number only open opened operator optional out pad parameter pass pause pending pointer pos position precision print private procedure program protected public quote read readwrite real rec recl recursive result return rewind save select selectcase selecttype sequential sign size stat status stop stream submodule subroutine target then to type unformatted unit use value volatile wait where while write"
"abs achar acos acosd adjustl adjustr aimag aimax0 aimin0 aint ajmax0 ajmin0 akmax0 akmin0 all allocated alog alog10 amax0 amax1 amin0 amin1 amod anint any asin asind associated atan atan2 atan2d atand bitest bitl bitlr bitrl bjtest bit_size bktest break btest cabs ccos cdabs cdcos cdexp cdlog cdsin cdsqrt ceiling cexp char clog cmplx conjg cos cosd cosh count cpu_time cshift csin csqrt dabs dacos dacosd dasin dasind datan datan2 datan2d datand date date_and_time dble dcmplx dconjg dcos dcosd dcosh dcotan ddim dexp dfloat dflotk dfloti dflotj digits dim dimag dint dlog dlog10 dmax1 dmin1 dmod dnint dot_product dprod dreal dsign dsin dsind dsinh dsqrt dtan dtand dtanh eoshift epsilon errsns exp exponent float floati floatj floatk floor fraction free huge iabs iachar iand ibclr ibits ibset ichar idate idim idint idnint ieor ifix iiabs iiand iibclr iibits iibset iidim iidint iidnnt iieor iifix iint iior iiqint iiqnnt iishft iishftc iisign ilen imax0 imax1 imin0 imin1 imod index inint inot int int1 int2 int4 int8 iqint iqnint ior ishft ishftc isign isnan izext jiand jibclr jibits jibset jidim jidint jidnnt jieor jifix jint jior jiqint jiqnnt jishft jishftc jisign jmax0 jmax1 jmin0 jmin1 jmod jnint jnot jzext kiabs kiand kibclr kibits kibset kidim kidint kidnnt kieor kifix kind kint kior kishft kishftc kisign kmax0 kmax1 kmin0 kmin1 kmod knint knot kzext lbound leadz len len_trim lenlge lge lgt lle llt log log10 logical lshift malloc matmul max max0 max1 maxexponent maxloc maxval merge min min0 min1 minexponent minloc minval mod modulo mvbits nearest nint not nworkers number_of_processors pack popcnt poppar precision present product radix random random_number random_seed range real repeat reshape rrspacing rshift scale scan secnds selected_int_kind selected_real_kind set_exponent shape sign sin sind sinh size sizeof sngl snglq spacing spread sqrt sum system_clock tan tand tanh tiny transfer transpose trim ubound unpack verify"
"cdabs cdcos cdexp cdlog cdsin cdsqrt cotan cotand dcmplx dconjg dcotan dcotand decode dimag dll_export dll_import doublecomplex dreal dvchk encode find flen flush getarg getcharqq getcl getdat getenv gettim hfix ibchng identifier imag int1 int2 int4 intc intrup invalop iostat_msg isha ishc ishl jfix lacfar locking locnear map nargs nbreak ndperr ndpexc offset ovefl peekcharqq precfill prompt qabs qacos qacosd qasin qasind qatan qatand qatan2 qcmplx qconjg qcos qcosd qcosh qdim qexp qext qextd qfloat qimag qlog qlog10 qmax1 qmin1 qmod qreal qsign qsin qsind qsinh qsqrt qtan qtand qtanh ran rand randu rewrite segment setdat settim system timer undfl unlock union val virtual volatile zabs zcos zexp zlog zsin zsqrt"
"cdabs cdcos cdexp cdlog cdsin cdsqrt cotan cotand dcmplx dconjg dcotan dcotand decode dimag dll_export dll_import doublecomplex dreal dvchk encode find flen flush getarg getcharqq getcl getdat getenv gettim hfix ibchng identifier imag int1 int2 int4 intc intrup invalop iostat_msg isha ishc ishl jfix lacfar locking locnear map nargs nbreak ndperr ndpexc offset ovefl peekcharqq precfill prompt qabs qacos qacosd qasin qasind qatan qatand qatan2 qcmplx qconjg qcos qcosd qcosh qdim qexp qext qextd qfloat qimag qlog qlog10 qmax1 qmin1 qmod qreal qsign qsin qsind qsinh qsqrt qtan qtand qtanh ran rand randu rewrite segment setdat settim system timer undfl unlock union val virtual volatile zabs zcos zexp zlog zsin zsqrt";
// color text
static SScintillaColors g_rgb_Syntax_fortran77[] =
{ {} };

//--------------------------------
//---- freebasic Language
//--------------------------------
// language
static CString g_str_freebasic_language = _T("freebasic");
// extentions
static CString g_str_freebasic_extention = _T("freebasic");
// comment line
static CString g_str_freebasic_commentline = _T("");
// comment start
static CString g_str_freebasic_commentStart = _T("");
// comment end
static CString g_str_freebasic_commentEnd = _T("");
// keywords
static const char* g_freebasic_KeyWords =
"append as asc asin asm atan2 atn beep bin binary bit bitreset bitset bload bsave byref byte byval call callocate case cbyte cdbl cdecl chain chdir chr cint circle clear clng clngint close cls color command common cons const continue cos cshort csign csng csrlin cubyte cuint culngint cunsg curdir cushort custom cvd cvi cvl cvlongint cvs cvshort data date deallocate declare defbyte defdbl defined defint deflng deflngint defshort defsng defstr defubyte defuint defulngint defushort dim dir do double draw dylibload dylibsymbol else elseif end enum environ environ$ eof eqv erase err error exec exepath exit exp export extern field fix flip for fre freefile function get getjoystick getkey getmouse gosub goto hex hibyte hiword if iif imagecreate imagedestroy imp inkey inp input instr int integer is kill lbound lcase left len let lib line lobyte loc local locate lock lof log long longint loop loword lset ltrim mid mkd mkdir mki mkl mklongint mks mkshort mod multikey mutexcreate mutexdestroy mutexlock mutexunlock name next not oct on once open option or out output overload paint palette pascal pcopy peek peeki peeks pipe pmap point pointer poke pokei pokes pos preserve preset print private procptr pset ptr public put random randomize read reallocate redim rem reset restore resume resume next return rgb rgba right rmdir rnd rset rtrim run sadd screen screencopy screeninfo screenlock screenptr screenres screenset screensync screenunlock seek statement seek function selectcase setdate setenviron setmouse settime sgn shared shell shl short shr sin single sizeof sleep space spc sqr static stdcall step stop str string string strptr sub swap system tab tan then threadcreate threadwait time time timer to trans trim type ubound ubyte ucase uinteger ulongint union unlock unsigned until ushort using va_arg va_first va_next val val64 valint varptr view viewprint wait wend while width window windowtitle with write xor zstring"
"#define #dynamic #else #endif #error #if #ifdef #ifndef #inclib #include #print #static #undef"
""
""
"";
// color text
static SScintillaColors g_rgb_Syntax_freebasic[] =
{ {} };

//--------------------------------
//---- gui4cli Language
//--------------------------------
// language
static CString g_str_gui4cli_language = _T("gui4cli");
// extentions
static CString g_str_gui4cli_extention = _T("gui4cli");
// comment line
static CString g_str_gui4cli_commentline = _T("");
// comment start
static CString g_str_gui4cli_commentStart = _T("");
// comment end
static CString g_str_gui4cli_commentEnd = _T("");
// keywords
static const char* g_gui4cli_KeyWords =
""
""
""
""
""
"";
// color text
static SScintillaColors g_rgb_Syntax_gui4cli[] =
{ {} };

//--------------------------------
//---- haskell Language
//--------------------------------
// language
static CString g_str_haskell_language = _T("haskell");
// extentions
static CString g_str_haskell_extention = _T("haskell");
// comment line
static CString g_str_haskell_commentline = _T("--");
// comment start
static CString g_str_haskell_commentStart = _T("");
// comment end
static CString g_str_haskell_commentEnd = _T("");
// keywords
static const char* g_haskell_KeyWords =
"as case class data default deriving do else hiding if import in infix infixl infixr instance let module newtype of proc qualified rec then type where _"
"as case class data default deriving do else hiding if import in infix infixl infixr instance let module newtype of proc qualified rec then type where _";
// color text
static SScintillaColors g_rgb_Syntax_haskell[] =
{ {} };

//--------------------------------
//---- html Language
//--------------------------------
// language
static CString g_str_html_language = _T("html");
// extentions
static CString g_str_html_extention = _T("html");
// comment line
static CString g_str_html_commentline = _T("");
// comment start
static CString g_str_html_commentStart = _T("<!--");
// comment end
static CString g_str_html_commentEnd = _T("-->");
// keywords
static const char* g_html_KeyWords =
"!doctype a abbr accept accept-charset accesskey acronym action address align alink alt applet archive area article aside async audio autocomplete autofocus axis b background base basefont bdi bdo bgcolor bgsound big blink blockquote body border br button canvas caption cellpadding cellspacing center char charoff charset checkbox checked cite class classid clear code codebase codetype col colgroup color cols colspan command compact content contenteditable contextmenu coords data datafld dataformatas datalist datapagesize datasrc datetime dd declare defer del details dfn dialog dir disabled div dl draggable dropzone dt element em embed enctype event face fieldset figcaption figure file font footer for form formaction formenctype formmethod formnovalidate formtarget frame frameborder frameset h1 h2 h3 h4 h5 h6 head header headers height hgroup hidden hr href hreflang hspace html http-equiv i id iframe image img input ins isindex ismap kbd keygen label lang language leftmargin legend li link list listing longdesc main manifest map marginheight marginwidth mark marquee max maxlength media menu menuitem meta meter method min multicol multiple name nav nobr noembed noframes nohref noresize noscript noshade novalidate nowrap object ol onabort onafterprint onautocomplete onautocompleteerror onbeforeonload onbeforeprint onblur oncancel oncanplay oncanplaythrough onchange onclick onclose oncontextmenu oncuechange ondblclick ondrag ondragend ondragenter ondragleave ondragover ondragstart ondrop ondurationchange onemptied onended onerror onfocus onhashchange oninput oninvalid onkeydown onkeypress onkeyup onload onloadeddata onloadedmetadata onloadstart onmessage onmousedown onmouseenter onmouseleave onmousemove onmouseout onmouseover onmouseup onmousewheel onoffline ononline onpagehide onpageshow onpause onplay onplaying onpointercancel onpointerdown onpointerenter onpointerleave onpointerlockchange onpointerlockerror onpointermove onpointerout onpointerover onpointerup onpopstate onprogress onratechange onreadystatechange onredo onreset onresize onscroll onseeked onseeking onselect onshow onsort onstalled onstorage onsubmit onsuspend ontimeupdate ontoggle onundo onunload onvolumechange onwaiting optgroup option output p param password pattern picture placeholder plaintext pre profile progress prompt public q radio readonly rel required reset rev reversed role rows rowspan rp rt rtc ruby rules s samp sandbox scheme scope scoped script seamless section select selected shadow shape size sizes small source spacer span spellcheck src srcdoc standby start step strike strong style sub submit summary sup svg svg:svg tabindex table target tbody td template text textarea tfoot th thead time title topmargin tr track tt type u ul usemap valign value valuetype var version video vlink vspace wbr width xml xmlns xmp"
"!doctype a abbr accept accept-charset accesskey acronym action address align alink alt applet archive area article aside async audio autocomplete autofocus axis b background base basefont bdi bdo bgcolor bgsound big blink blockquote body border br button canvas caption cellpadding cellspacing center char charoff charset checkbox checked cite class classid clear code codebase codetype col colgroup color cols colspan command compact content contenteditable contextmenu coords data datafld dataformatas datalist datapagesize datasrc datetime dd declare defer del details dfn dialog dir disabled div dl draggable dropzone dt element em embed enctype event face fieldset figcaption figure file font footer for form formaction formenctype formmethod formnovalidate formtarget frame frameborder frameset h1 h2 h3 h4 h5 h6 head header headers height hgroup hidden hr href hreflang hspace html http-equiv i id iframe image img input ins isindex ismap kbd keygen label lang language leftmargin legend li link list listing longdesc main manifest map marginheight marginwidth mark marquee max maxlength media menu menuitem meta meter method min multicol multiple name nav nobr noembed noframes nohref noresize noscript noshade novalidate nowrap object ol onabort onafterprint onautocomplete onautocompleteerror onbeforeonload onbeforeprint onblur oncancel oncanplay oncanplaythrough onchange onclick onclose oncontextmenu oncuechange ondblclick ondrag ondragend ondragenter ondragleave ondragover ondragstart ondrop ondurationchange onemptied onended onerror onfocus onhashchange oninput oninvalid onkeydown onkeypress onkeyup onload onloadeddata onloadedmetadata onloadstart onmessage onmousedown onmouseenter onmouseleave onmousemove onmouseout onmouseover onmouseup onmousewheel onoffline ononline onpagehide onpageshow onpause onplay onplaying onpointercancel onpointerdown onpointerenter onpointerleave onpointerlockchange onpointerlockerror onpointermove onpointerout onpointerover onpointerup onpopstate onprogress onratechange onreadystatechange onredo onreset onresize onscroll onseeked onseeking onselect onshow onsort onstalled onstorage onsubmit onsuspend ontimeupdate ontoggle onundo onunload onvolumechange onwaiting optgroup option output p param password pattern picture placeholder plaintext pre profile progress prompt public q radio readonly rel required reset rev reversed role rows rowspan rp rt rtc ruby rules s samp sandbox scheme scope scoped script seamless section select selected shadow shape size sizes small source spacer span spellcheck src srcdoc standby start step strike strong style sub submit summary sup svg svg:svg tabindex table target tbody td template text textarea tfoot th thead time title topmargin tr track tt type u ul usemap valign value valuetype var version video vlink vspace wbr width xml xmlns xmp";
// color text
static SScintillaColors g_rgb_Syntax_html[] =
{ {} };

//--------------------------------
//---- ini Language
//--------------------------------
// language
static CString g_str_ini_language = _T("ini");
// extentions
static CString g_str_ini_extention = _T("ini");
// comment line
static CString g_str_ini_commentline = _T(";");
// comment start
static CString g_str_ini_commentStart = _T("");
// comment end
static CString g_str_ini_commentEnd = _T("");
// keywords
static const char* g_ini_KeyWords =
// color text
static SScintillaColors g_rgb_Syntax_ini[] =
{ {} };

//--------------------------------
//---- inno Language
//--------------------------------
// language
static CString g_str_inno_language = _T("inno");
// extentions
static CString g_str_inno_extention = _T("inno");
// comment line
static CString g_str_inno_commentline = _T(";");
// comment start
static CString g_str_inno_commentStart = _T("");
// comment end
static CString g_str_inno_commentEnd = _T("");
// keywords
static const char* g_inno_KeyWords =
"code components custommessages dirs files icons ini installdelete langoptions languages messages registry run setup types tasks uninstalldelete uninstallrun _istool"
"allowcancelduringinstall allownoicons allowrootdirectory allowuncpath alwaysrestart alwaysshowcomponentslist alwaysshowdironreadypage alwaysshowgrouponreadypage alwaysusepersonalgroup appcomments appcontact appcopyright appenddefaultdirname appenddefaultgroupname appid appmodifypath appmutex appname apppublisher apppublisherurl appreadmefile appsupporturl appupdatesurl appvername appversion architecturesallowed architecturesinstallin64bitmode backcolor backcolor2 backcolordirection backsolid changesassociations changesenvironment compression copyrightfontname copyrightfontsize createappdir createuninstallregkey defaultdirname defaultgroupname defaultuserinfoname defaultuserinfoorg defaultuserinfoserial dialogfontname dialogfontsize direxistswarning disabledirpage disablefinishedpage disableprogramgrouppage disablereadymemo disablereadypage disablestartupprompt diskclustersize diskslicesize diskspanning enablesdirdoesntexistwarning encryption extradiskspacerequired flatcomponentslist infoafterfile infobeforefile internalcompresslevel languagedetectionmethod languagecodepage languageid languagename licensefile lzmanumfastbytes mergeduplicatefiles minversion onlybelowversion outputbasefilename outputdir outputmanifestfile password privilegesrequired reservebytes restartifneededbyrun setupiconfile showcomponentsizes showlanguagedialog showtaskstreelines slicesperdisk solidcompression sourcedir timestamprounding timestampsinutc titlefontname titlefontsize touchdate touchtime uninstallable uninstalldisplayicon uninstalldisplayname uninstallfilesdir uninstalllogmode uninstallrestartcomputer updateuninstalllogappname usepreviousappdir usepreviousgroup useprevioussetuptype useprevioustasks useprevioususerinfo userinfopage usesetupldr versioninfocompany versioninfocopyright versioninfodescription versioninfotextversion versioninfoversion welcomefontname welcomefontsize windowshowcaption windowstartmaximized windowresizable windowvisible wizardimagebackcolor wizardimagefile wizardimagestretch wizardsmallimagefile"
"afterinstall attribs beforeinstall check comment components copymode description destdir destname excludes extradiskspacerequired filename flags fontinstall groupdescription hotkey infoafterfile infobeforefile iconfilename iconindex key languages licensefile messagesfile minversion name onlybelowversion parameters permissions root runonceid section source statusmsg string subkey tasks type types valuedata valuename valuetype workingdir"
"append define dim elif else emit endif endsub error expr file for if ifdef ifexist ifndef ifnexist include insert pragma sub undef"
"begin break case const continue do downto else end except finally for function if of procedure repeat then to try until uses var while with"
""
"";
// color text
static SScintillaColors g_rgb_Syntax_inno[] =
{ {} };

//--------------------------------
//---- ihex Language
//--------------------------------
// language
static CString g_str_ihex_language = _T("ihex");
// extentions
static CString g_str_ihex_extention = _T("ihex");
// comment line
static CString g_str_ihex_commentline = _T("");
// comment start
static CString g_str_ihex_commentStart = _T("");
// comment end
static CString g_str_ihex_commentEnd = _T("");
// keywords
static const char* g_ihex_KeyWords =
// color text
static SScintillaColors g_rgb_Syntax_ihex[] =
{ {} };

//--------------------------------
//---- java Language
//--------------------------------
// language
static CString g_str_java_language = _T("java");
// extentions
static CString g_str_java_extention = _T("java");
// comment line
static CString g_str_java_commentline = _T("//");
// comment start
static CString g_str_java_commentStart = _T("/*");
// comment end
static CString g_str_java_commentEnd = _T("*/");
// keywords
static const char* g_java_KeyWords =
"instanceof assert if else switch case default break goto return for while do continue new throw throws try catch finally this super extends implements import true false null"
"package transient strictfp void char short int long double float const static volatile byte boolean class interface native private protected public final abstract synchronized enum"
"package transient strictfp void char short int long double float const static volatile byte boolean class interface native private protected public final abstract synchronized enum";
// color text
static SScintillaColors g_rgb_Syntax_java[] =
{ {} };

//--------------------------------
//---- javascript Language
//--------------------------------
// language
static CString g_str_javascript_language = _T("javascript");
// extentions
static CString g_str_javascript_extention = _T("javascript");
// comment line
static CString g_str_javascript_commentline = _T("//");
// comment start
static CString g_str_javascript_commentStart = _T("/*");
// comment end
static CString g_str_javascript_commentEnd = _T("*/");
// keywords
static const char* g_javascript_KeyWords =
"abstract async await boolean break byte case catch char class const continue debugger default delete do double else enum export extends final finally float for function goto if implements import in instanceof int interface let long native new null of package private protected public return short static super switch synchronized this throw throws transient try typeof var void volatile while with true false prototype yield"
"abstract async await boolean break byte case catch char class const continue debugger default delete do double else enum export extends final finally float for function goto if implements import in instanceof int interface let long native new null of package private protected public return short static super switch synchronized this throw throws transient try typeof var void volatile while with true false prototype yield";
// color text
static SScintillaColors g_rgb_Syntax_javascript[] =
{ {} };

//--------------------------------
//---- javascript.js Language
//--------------------------------
// language
static CString g_str_javascript.js_language = _T("javascript.js");
// extentions
static CString g_str_javascript.js_extention = _T("javascript.js");
// comment line
static CString g_str_javascript.js_commentline = _T("//");
// comment start
static CString g_str_javascript.js_commentStart = _T("/*");
// comment end
static CString g_str_javascript.js_commentEnd = _T("*/");
// keywords
static const char* g_javascript.js_KeyWords =
"abstract async await boolean break byte case catch char class const continue debugger default delete do double else enum export extends final finally float for function goto if implements import in instanceof int interface let long native new null of package private protected public return short static super switch synchronized this throw throws transient try typeof var void volatile while with true false prototype yield"
"Array Date eval hasOwnProperty Infinity isFinite isNaN isPrototypeOf Math NaN Number Object prototype String toString undefined valueOf"
"alert all anchor anchors area assign blur button checkbox clearInterval clearTimeout clientInformation close closed confirm constructor crypto decodeURI decodeURIComponent defaultStatus document element elements embed embeds encodeURI encodeURIComponent escape event fileUpload focus form forms frame innerHeight innerWidth layer layers link location mimeTypes navigate navigator frames frameRate hidden history image images offscreenBuffering onblur onclick onerror onfocus onkeydown onkeypress onkeyup onmouseover onload onmouseup onmousedown onsubmit open opener option outerHeight outerWidth packages pageXOffset pageYOffset parent parseFloat parseInt password pkcs11 plugin prompt propertyIsEnum radio reset screenX screenY scroll secure select self setInterval setTimeout status submit taint text textarea top unescape untaint window"
"alert all anchor anchors area assign blur button checkbox clearInterval clearTimeout clientInformation close closed confirm constructor crypto decodeURI decodeURIComponent defaultStatus document element elements embed embeds encodeURI encodeURIComponent escape event fileUpload focus form forms frame innerHeight innerWidth layer layers link location mimeTypes navigate navigator frames frameRate hidden history image images offscreenBuffering onblur onclick onerror onfocus onkeydown onkeypress onkeyup onmouseover onload onmouseup onmousedown onsubmit open opener option outerHeight outerWidth packages pageXOffset pageYOffset parent parseFloat parseInt password pkcs11 plugin prompt propertyIsEnum radio reset screenX screenY scroll secure select self setInterval setTimeout status submit taint text textarea top unescape untaint window";
// color text
static SScintillaColors g_rgb_Syntax_javascript.js[] =
{ {} };

//--------------------------------
//---- json Language
//--------------------------------
// language
static CString g_str_json_language = _T("json");
// extentions
static CString g_str_json_extention = _T("json");
// comment line
static CString g_str_json_commentline = _T("");
// comment start
static CString g_str_json_commentStart = _T("");
// comment end
static CString g_str_json_commentEnd = _T("");
// keywords
static const char* g_json_KeyWords =
"false null true"
"@id @context @type @value @language @container @list @set @reverse @index @base @vocab @graph"
"@id @context @type @value @language @container @list @set @reverse @index @base @vocab @graph";
// color text
static SScintillaColors g_rgb_Syntax_json[] =
{ {} };

//--------------------------------
//---- jsp Language
//--------------------------------
// language
static CString g_str_jsp_language = _T("jsp");
// extentions
static CString g_str_jsp_extention = _T("jsp");
// comment line
static CString g_str_jsp_commentline = _T("//");
// comment start
static CString g_str_jsp_commentStart = _T("/*");
// comment end
static CString g_str_jsp_commentEnd = _T("*/");
// keywords
static const char* g_jsp_KeyWords =
// color text
static SScintillaColors g_rgb_Syntax_jsp[] =
{ {} };

//--------------------------------
//---- kix Language
//--------------------------------
// language
static CString g_str_kix_language = _T("kix");
// extentions
static CString g_str_kix_extention = _T("kix");
// comment line
static CString g_str_kix_commentline = _T(";");
// comment start
static CString g_str_kix_commentStart = _T("");
// comment end
static CString g_str_kix_commentEnd = _T("");
// keywords
static const char* g_kix_KeyWords =
"? and beep big break call cd cls color cookie1 copy debug del dim display do until exit flushkb for each next function endfunction get gets global go gosub goto if else endif md or password play quit rd redim return run select case endselect set setl setm settime shell sleep small use while loop"
"abs addkey addprinterconnection addprogramgroup addprogramitem asc ascan at backupeventlog box cdbl chr cint cleareventlog close comparefiletimes createobject cstr dectohex delkey delprinterconnection delprogramgroup delprogramitem deltree delvalue dir enumgroup enumipinfo enumkey enumlocalgroup enumvalue execute exist existkey expandenvironmentvars fix formatnumber freefilehandle getdiskspace getfileattr getfilesize getfiletime getfileversion getobject iif ingroup instr instrrev int isdeclared join kbhit keyexist lcase left len loadhive loadkey logevent logoff ltrim memorysize messagebox open readline readprofilestring readtype readvalue redirectoutput right rnd round rtrim savekey sendkeys sendmessage setascii setconsole setdefaultprinter setfileattr setfocus setoption setsystemstate settitle setwallpaper showprogramgroup shutdown sidtoname split srnd substr trim ubound ucase unloadhive val vartype vartypename writeline writeprofilestring writevalue"
"address build color comment cpu crlf csd curdir date day domain dos error fullname homedir homedrive homeshr hostname inwin ipaddress0 ipaddress1 ipaddress2 ipaddress3 kix lanroot ldomain ldrive lm logonmode longhomedir lserver maxpwage mdayno mhz monthno month msecs pid primarygroup priv productsuite producttype pwage ras result rserver scriptdir scriptexe scriptname serror sid site startdir syslang ticks time userid userlang wdayno wksta wuserid ydayno year"
"address build color comment cpu crlf csd curdir date day domain dos error fullname homedir homedrive homeshr hostname inwin ipaddress0 ipaddress1 ipaddress2 ipaddress3 kix lanroot ldomain ldrive lm logonmode longhomedir lserver maxpwage mdayno mhz monthno month msecs pid primarygroup priv productsuite producttype pwage ras result rserver scriptdir scriptexe scriptname serror sid site startdir syslang ticks time userid userlang wdayno wksta wuserid ydayno year";
// color text
static SScintillaColors g_rgb_Syntax_kix[] =
{ {} };

//--------------------------------
//---- lisp Language
//--------------------------------
// language
static CString g_str_lisp_language = _T("lisp");
// extentions
static CString g_str_lisp_extention = _T("lisp");
// comment line
static CString g_str_lisp_commentline = _T(";");
// comment start
static CString g_str_lisp_commentStart = _T("");
// comment end
static CString g_str_lisp_commentEnd = _T("");
// keywords
static const char* g_lisp_KeyWords =
"not defun + - * / = < > <= >= princ eval apply funcall quote identity function complement backquote lambda set setq setf defmacro gensym make symbol intern name value plist get getf putprop remprop hash array aref car cdr caar cadr cdar cddr caaar caadr cadar caddr cdaar cdadr cddar cdddr caaaar caaadr caadar caaddr cadaar cadadr caddar cadddr cdaaar cdaadr cdadar cdaddr cddaar cddadr cdddar cddddr cons list append reverse last nth nthcdr member assoc subst sublis nsubst nsublis remove length mapc mapcar mapl maplist mapcan mapcon rplaca rplacd nconc delete atom symbolp numberp boundp null listp consp minusp zerop plusp evenp oddp eq eql equal cond case and or let l if prog prog1 prog2 progn go return do dolist dotimes catch throw error cerror break continue errset baktrace evalhook truncate float rem min max abs sin cos tan expt exp sqrt random logand logior logxor lognot bignums logeqv lognand lognor logorc2 logtest logbitp logcount integer nil"
""
"";
// color text
static SScintillaColors g_rgb_Syntax_lisp[] =
{ {} };

//--------------------------------
//---- latex Language
//--------------------------------
// language
static CString g_str_latex_language = _T("latex");
// extentions
static CString g_str_latex_extention = _T("latex");
// comment line
static CString g_str_latex_commentline = _T("");
// comment start
static CString g_str_latex_commentStart = _T("");
// comment end
static CString g_str_latex_commentEnd = _T("");
// keywords
static const char* g_latex_KeyWords =
// color text
static SScintillaColors g_rgb_Syntax_latex[] =
{ {} };

//--------------------------------
//---- lua Language
//--------------------------------
// language
static CString g_str_lua_language = _T("lua");
// extentions
static CString g_str_lua_extention = _T("lua");
// comment line
static CString g_str_lua_commentline = _T("--");
// comment start
static CString g_str_lua_commentStart = _T("");
// comment end
static CString g_str_lua_commentEnd = _T("");
// keywords
static const char* g_lua_KeyWords =
"and break do else elseif end false for function goto if in local nil not or repeat return then true until while"
"_ENV _G _VERSION assert collectgarbage dofile error getfenv getmetatable ipairs load loadfile loadstring module next pairs pcall print rawequal rawget rawlen rawset require select setfenv setmetatable tonumber tostring type unpack xpcall string table math bit32 coroutine io os debug package __index __newindex __call __add __sub __mul __div __mod __pow __unm __concat __len __eq __lt __le __gc __mode"
"byte char dump find format gmatch gsub len lower match rep reverse sub upper abs acos asin atan atan2 ceil cos cosh deg exp floor fmod frexp ldexp log log10 max min modf pow rad random randomseed sin sinh sqrt tan tanh arshift band bnot bor btest bxor extract lrotate lshift replace rrotate rshift shift string.byte string.char string.dump string.find string.format string.gmatch string.gsub string.len string.lower string.match string.rep string.reverse string.sub string.upper table.concat table.insert table.maxn table.pack table.remove table.sort table.unpack math.abs math.acos math.asin math.atan math.atan2 math.ceil math.cos math.cosh math.deg math.exp math.floor math.fmod math.frexp math.huge math.ldexp math.log math.log10 math.max math.min math.modf math.pi math.pow math.rad math.random math.randomseed math.sin math.sinh math.sqrt math.tan math.tanh bit32.arshift bit32.band bit32.bnot bit32.bor bit32.btest bit32.bxor bit32.extract bit32.lrotate bit32.lshift bit32.replace bit32.rrotate bit32.rshift"
"close flush lines read seek setvbuf write clock date difftime execute exit getenv remove rename setlocale time tmpname coroutine.create coroutine.resume coroutine.running coroutine.status coroutine.wrap coroutine.yield io.close io.flush io.input io.lines io.open io.output io.popen io.read io.tmpfile io.type io.write io.stderr io.stdin io.stdout os.clock os.date os.difftime os.execute os.exit os.getenv os.remove os.rename os.setlocale os.time os.tmpname debug.debug debug.getfenv debug.gethook debug.getinfo debug.getlocal debug.getmetatable debug.getregistry debug.getupvalue debug.getuservalue debug.setfenv debug.sethook debug.setlocal debug.setmetatable debug.setupvalue debug.setuservalue debug.traceback debug.upvalueid debug.upvaluejoin package.cpath package.loaded package.loaders package.loadlib package.path package.preload package.seeall"
"close flush lines read seek setvbuf write clock date difftime execute exit getenv remove rename setlocale time tmpname coroutine.create coroutine.resume coroutine.running coroutine.status coroutine.wrap coroutine.yield io.close io.flush io.input io.lines io.open io.output io.popen io.read io.tmpfile io.type io.write io.stderr io.stdin io.stdout os.clock os.date os.difftime os.execute os.exit os.getenv os.remove os.rename os.setlocale os.time os.tmpname debug.debug debug.getfenv debug.gethook debug.getinfo debug.getlocal debug.getmetatable debug.getregistry debug.getupvalue debug.getuservalue debug.setfenv debug.sethook debug.setlocal debug.setmetatable debug.setupvalue debug.setuservalue debug.traceback debug.upvalueid debug.upvaluejoin package.cpath package.loaded package.loaders package.loadlib package.path package.preload package.seeall";
// color text
static SScintillaColors g_rgb_Syntax_lua[] =
{ {} };

//--------------------------------
//---- makefile Language
//--------------------------------
// language
static CString g_str_makefile_language = _T("makefile");
// extentions
static CString g_str_makefile_extention = _T("makefile");
// comment line
static CString g_str_makefile_commentline = _T("#");
// comment start
static CString g_str_makefile_commentStart = _T("");
// comment end
static CString g_str_makefile_commentEnd = _T("");
// keywords
static const char* g_makefile_KeyWords =
// color text
static SScintillaColors g_rgb_Syntax_makefile[] =
{ {} };

//--------------------------------
//---- matlab Language
//--------------------------------
// language
static CString g_str_matlab_language = _T("matlab");
// extentions
static CString g_str_matlab_extention = _T("matlab");
// comment line
static CString g_str_matlab_commentline = _T("%");
// comment start
static CString g_str_matlab_commentStart = _T("");
// comment end
static CString g_str_matlab_commentEnd = _T("");
// keywords
static const char* g_matlab_KeyWords =
"break case catch classdef continue else elseif end for function global if otherwise parfor persistent return switch try while"
"break case catch classdef continue else elseif end for function global if otherwise parfor persistent return switch try while";
// color text
static SScintillaColors g_rgb_Syntax_matlab[] =
{ {} };

//--------------------------------
//---- mmixal Language
//--------------------------------
// language
static CString g_str_mmixal_language = _T("mmixal");
// extentions
static CString g_str_mmixal_extention = _T("mmixal");
// comment line
static CString g_str_mmixal_commentline = _T("%");
// comment start
static CString g_str_mmixal_commentStart = _T("");
// comment end
static CString g_str_mmixal_commentEnd = _T("");
// keywords
static const char* g_mmixal_KeyWords =
"2ADDU 4ADDU 8ADDU 16ADDU ADD ADDU AND ANDNH ANDNL ANDNMH ANDNML BDIF BEV BN BNN BNP BNZ BOD BP BSPEC BYTE BZ CMP CMPU CSEV CSN CSNN CSNP CSNZ CSOD CSP CSWAP CSZ DIV DIVU ESPEC EXPR FADD FCMP FCMPE FDIV FEQL FEQLE FIX FIXU FLOT FLOTU FMUL FREM FSQRT FSUB FUN FUNE GET GETA GO GREG I_BIT INCH INCL INCMH INCML IS JMP LDA LDB LDBU LDHT LDO LDOU LDSF LDT LDTU LDUNC LDVTS LDW LDWU LOC LOCAL MOR MUL MULU MUX MXOR NAND NEG NEGU NNIX NOR NXOR O_BIT OCTA ODIF OR ORH ORL ORMH ORML ORN PBEV PBN PBNN PBNP PBNZ PBOD PBP PBZ POP PREFIX PREGO PRELD PREST PUSHGO PUSHJ PUT RESUME SAVE SET SETH SETL SETMH SETML SFLOT SFLOTU SL SLU SR SRU STB STBU STCO STHT STO STOU STSF STT STTU STUNC STW STWU SUB SUBU SWYM SYNC SYNCD TDIF TETRA TRAP TRIP UNSAVE WDIF WYDEXOR ZSEV ZSN ZSNN ZSNP ZSNZ ZSOD ZSP ZSZ"
"rA rB rC rD rE rF rG rH rI rJ rK rL rM rN rO rP rQ rR rS rT rU rV rW rX rY rZ rBB rTT rWW rXX rYY rZZ"
"@ Text_Segment Data_Segment Pool_Segment Stack_Segment StdErr StdIn StdOut Fopen Fclose Fread Fwrite Fgets Fputs Fgetws Fputws Ftell Fseek TextRead TextWrite BinaryRead BinaryWrite BinaryReadWrite"
"@ Text_Segment Data_Segment Pool_Segment Stack_Segment StdErr StdIn StdOut Fopen Fclose Fread Fwrite Fgets Fputs Fgetws Fputws Ftell Fseek TextRead TextWrite BinaryRead BinaryWrite BinaryReadWrite";
// color text
static SScintillaColors g_rgb_Syntax_mmixal[] =
{ {} };

//--------------------------------
//---- nimrod Language
//--------------------------------
// language
static CString g_str_nimrod_language = _T("nimrod");
// extentions
static CString g_str_nimrod_extention = _T("nimrod");
// comment line
static CString g_str_nimrod_commentline = _T("#");
// comment start
static CString g_str_nimrod_commentStart = _T("");
// comment end
static CString g_str_nimrod_commentEnd = _T("");
// keywords
static const char* g_nimrod_KeyWords =
"addr and as asm block break case cast const continue converter discard div elif else end enum except exception finally for from generic if implies import in include is isnot iterator lambda macro method mod nil not notin object of or out proc ptr raise ref return shl shr template try tuple type var when where while with without xor yield"
"addr and as asm block break case cast const continue converter discard div elif else end enum except exception finally for from generic if implies import in include is isnot iterator lambda macro method mod nil not notin object of or out proc ptr raise ref return shl shr template try tuple type var when where while with without xor yield";
// color text
static SScintillaColors g_rgb_Syntax_nimrod[] =
{ {} };

//--------------------------------
//---- nncrontab Language
//--------------------------------
// language
static CString g_str_nncrontab_language = _T("nncrontab");
// extentions
static CString g_str_nncrontab_extention = _T("nncrontab");
// comment line
static CString g_str_nncrontab_commentline = _T("\");
// comment start
static CString g_str_nncrontab_commentStart = _T("");
// comment end
static CString g_str_nncrontab_commentEnd = _T("");
// keywords
static const char* g_nncrontab_KeyWords =
"AGAIN ALLOT AND Action BEGIN CASE COMPARE CONSTANT CREATE DO Days ELSE ENDCASE ENDOF EVAL-SUBST EVALUATE FALSE Hours I IF LEAVE LOOP Minutes Months NOT OF OFF ON OR PAD REPEAT Rule SET THEN TRUE Time UNTIL VALUE VARIABLE WHILE WeekDays Years"
"</JScript> </SCRIPT> </VBScript> <JScript> <VBScript> ACCESS-DATE BEEP CALL_DIAL CALL_HANGUP CHAR CLIPBOARD CONSOLE CREATION-DATE CUR-DATE DATE- DATE-INTERVAL DELAY DIAL DIR-CREATE DIR-DELETE DIR-EMPTY DIR-SIZE Day@ Domain ERR-MSG EXIST FILE-ACCESS-DATE FILE-APPEND FILE-COPY FILE-CREATE FILE-CREATION-DATE FILE-CROP FILE-DATE FILE-DELETE FILE-EMPTY FILE-EXIST FILE-MOVE FILE-RENAME FILE-SIZE FILE-WRITE FILE-WRITE-DATE FOR-CHILD-WINDOWS FOR-FILES FOR-WINDOWS FREE-SPACE GET-CUR-TIME GET-REG GET-VER GetTickCount HANGUP HIDE-ICON HINT HINT-OFF HINT-POS HINT-SIZE HINTW HOST-EXIST Hour@ IDLE INTERVAL IS-ARCHIVE IS-DIR IS-HIDDEN IS-READONLY IS-SYSTEM KILL LAUNCH LOG LOGGEDON LOGOFF LogonBatch LogonInteractive LogonNetwork MOUSE-LBCLK MOUSE-LBDCLK MOUSE-LBDN MOUSE-LBUP MOUSE-MOVE MOUSE-MOVER MOUSE-MOVEW MOUSE-RBCLK MOUSE-RBDCLK MOUSE-RBDN MOUSE-RBUP MSG Min@ Mon@ MonitorResponseTime NHOST-EXIST No ONLINE PAUSE PLAY-SOUND PLAY-SOUNDW POP3-CHECK POWEROFF PROC-EXIST PROC-TIME PURGE-OLD PURGE-OLDA PURGE-OLDW Password QSTART-APP QSTART-APPW QUERY QUIT RASDomain RASError RASPassword RASPhone RASSecPassword RASUser RE-ALL RE-MATCH REBOOT REG-DELETE-KEY REG-DELETE-VALUE REG-DWORD REG-SZ REMINDER RUN SEND-KEYS SEND-KEYS-DELAY SHOW-ICON SHUTDOWN START-APP START-APPW START-QUIT START-TIME Sec@ SecPassword THINT THINTW TimeSec@ TMSG TQUERY User WDay@ WIN-ACTIVATE WIN-ACTIVE WIN-CLICK WIN-CLOSE WIN-EXIST WIN-HIDE WIN-HWND WIN-MAXIMIZE WIN-MINIMIZE WIN-MOVE WIN-MOVER WIN-RESTORE WIN-SEND-KEYS WIN-SHOW WIN-TERMINATE WIN-TOPMOST WIN-VER WIN-WAIT WINAPI WRITE-DATE WatchClipboard WatchConnect WatchDir WatchDisconnect WatchDriveInsert WatchDriveRemove WatchFile WatchProc WatchProcStop WatchWinActivate WatchWinCreate WatchWinDestroy WatchWindow WinNT Year@ Yes"
"ALL AboveNormalPriority AsService BelowNormalPriority FILESONLY HighPriority IdlePriority LoadProfile NoActive NoDel NoLog NoRunAs NormalPriority OnceADay OnceAHour OnceAMonth OnceAWeek RECURSIVE RealtimePriority RunOnce SWHide ShowMaximized ShowMinimized ShowNoActivate ShowNormal StartIn StartPos StartSize TODEPTH WATCH-CHANGE-ATTRIBUTES WATCH-CHANGE-DIR-NAME WATCH-CHANGE-FILE-NAME WATCH-CHANGE-LAST-WRITE WATCH-CHANGE-SECURITY WATCH-CHANGE-SIZE WaitFor WatchSubtree WithoutProfile"
"ALL AboveNormalPriority AsService BelowNormalPriority FILESONLY HighPriority IdlePriority LoadProfile NoActive NoDel NoLog NoRunAs NormalPriority OnceADay OnceAHour OnceAMonth OnceAWeek RECURSIVE RealtimePriority RunOnce SWHide ShowMaximized ShowMinimized ShowNoActivate ShowNormal StartIn StartPos StartSize TODEPTH WATCH-CHANGE-ATTRIBUTES WATCH-CHANGE-DIR-NAME WATCH-CHANGE-FILE-NAME WATCH-CHANGE-LAST-WRITE WATCH-CHANGE-SECURITY WATCH-CHANGE-SIZE WaitFor WatchSubtree WithoutProfile";
// color text
static SScintillaColors g_rgb_Syntax_nncrontab[] =
{ {} };

//--------------------------------
//---- nfo Language
//--------------------------------
// language
static CString g_str_nfo_language = _T("nfo");
// extentions
static CString g_str_nfo_extention = _T("nfo");
// comment line
static CString g_str_nfo_commentline = _T("");
// comment start
static CString g_str_nfo_commentStart = _T("");
// comment end
static CString g_str_nfo_commentEnd = _T("");
// keywords
static const char* g_nfo_KeyWords =
// color text
static SScintillaColors g_rgb_Syntax_nfo[] =
{ {} };

//--------------------------------
//---- nsis Language
//--------------------------------
// language
static CString g_str_nsis_language = _T("nsis");
// extentions
static CString g_str_nsis_extention = _T("nsis");
// comment line
static CString g_str_nsis_commentline = _T(";");
// comment start
static CString g_str_nsis_commentStart = _T("/*");
// comment end
static CString g_str_nsis_commentEnd = _T("*/");
// keywords
static const char* g_nsis_KeyWords =
"Abort AddBrandingImage AddSize AllowRootDirInstall AllowSkipFiles AutoCloseWindow BGFont BGGradient BrandingText BringToFront Call CallInstDLL Caption ChangeUI CheckBitmap ClearErrors CompletedText ComponentText CopyFiles CRCCheck CreateDirectory CreateFont CreateShortCut Delete DeleteINISec DeleteINIStr DeleteRegKey DeleteRegValue DetailPrint DetailsButtonText DirText DirVar DirVerify EnableWindow EnumRegKey EnumRegValue Exch Exec ExecShell ExecWait ExpandEnvStrings File FileBufSize FileClose FileErrorText FileOpen FileRead FileReadByte FileReadUTF16LE FileSeek FileWrite FileWriteByte FileWriteUTF16LE FindClose FindFirst FindNext FindWindow FlushINI Function FunctionEnd GetCurInstType GetCurrentAddress GetDlgItem GetDLLVersion GetDLLVersionLocal GetErrorLevel GetExeName GetExePath GetFileTime GetFileTimeLocal GetFullPathName GetFunctionAddress GetInstDirError GetLabelAddress GetTempFileName Goto HideWindow Icon IfAbort IfErrors IfFileExists IfRebootFlag IfSilent InitPluginsDir InstallButtonText InstallColors InstallDir InstallDirRegKey InstProgressFlags InstType InstTypeGetText InstTypeSetText IntCmp IntCmpU IntFmt IntOp IsWindow LangString LangStringUP LicenseBkColor LicenseData LicenseForceSelection LicenseLangString LicenseText LoadLanguageFile LockWindow LogSet LogText ManifestDPIAware ManifestSupportedOS MessageBox MiscButtonText Nop Name OutFile Page PageEx PageExEnd PluginDir Pop Push Quit ReadEnvStr ReadINIStr ReadRegDWORD ReadRegStr Reboot RegDLL Rename RequestExecutionLevel ReserveFile Return RMDir SearchPath Section SectionEnd SectionGetFlags SectionGetInstTypes SectionGetSize SectionGetText SectionGroup SectionGroupEnd SectionIn SectionSetFlags SectionSetInstTypes SectionSetSize SectionSetText SendMessage SetAutoClose SetBrandingImage SetCompress SetCompressionLevel SetCompressor SetCompressorDictSize SetCtlColors SetCurInstType SetDatablockOptimize SetDateSave SetDetailsPrint SetDetailsView SetErrorLevel SetErrors SetFileAttributes SetFont SetOutPath SetOverwrite SetPluginUnload SetRebootFlag SetRegView SetShellVarContext SetSilent SetStaticBkColor ShowInstDetails ShowUninstDetails ShowWindow SilentInstall SilentUnInstall Sleep SpaceTexts StrCmp StrCmpS StrCpy StrLen SubSection SubSectionEnd Unicode UninstallButtonText UninstallCaption UninstallIcon UninstallSubCaption UninstallText UninstPage UnRegDLL UnsafeStrCpy Var VIAddVersionKey VIFileVersion VIProductVersion WindowIcon WriteINIStr WriteRegBin WriteRegDWORD WriteRegExpandStr WriteRegStr WriteUninstaller XPStyle !AddIncludeDir !AddPluginDir !appendfile !cd !define !delfile !echo !else !endif !error !execute !finalize !getdllversion !if !ifdef !ifmacrodef !ifmacrondef !ifndef !include !insertmacro !macro !macroend !macroundef !packhdr !searchparse !searchreplace !system !tempfile !undef !verbose !warning"
"$0 $1 $2 $3 $4 $5 $6 $7 $8 $9 $R0 $R1 $R2 $R3 $R4 $R5 $R6 $R7 $R8 $R9 $ADMINTOOLS $APPDATA $CDBURN_AREA $CMDLINE $COMMONFILES $COMMONFILES32 $COMMONFILES64 $COOKIES $DESKTOP $DOCUMENTS $EXEDIR $EXEFILE $EXEPATH $FAVORITES $FONTS $HISTORY $HWNDPARENT $INTERNET_CACHE $INSTDIR $LANGUAGE $LOCALAPPDATA $MUSIC $NETHOOD ${NSISDIR} $OUTDIR $PICTURES $PLUGINSDIR $PRINTHOOD $PROFILE $PROGRAMFILES $PROGRAMFILES32 $PROGRAMFILES64 $QUICKLAUNCH $RECENT $RESOURCES $RESOURCES_LOCALIZED $SENDTO $SMPROGRAMS $SMSTARTUP $STARTMENU $SYSDIR $TEMP $TEMPLATES $VIDEOS $WINDIR $$ $\n $\r $\t"
"ARCHIVE CUR END FILE_ATTRIBUTE_ARCHIVE FILE_ATTRIBUTE_HIDDEN FILE_ATTRIBUTE_NORMAL FILE_ATTRIBUTE_OFFLINE FILE_ATTRIBUTE_READONLY FILE_ATTRIBUTE_SYSTEM FILE_ATTRIBUTE_TEMPORARY HIDDEN HKCC HKCR HKCU HKDD HKEY_CLASSES_ROOT HKEY_CURRENT_CONFIG HKEY_CURRENT_USER HKEY_DYN_DATA HKEY_LOCAL_MACHINE HKEY_PERFORMANCE_DATA HKEY_USERS HKLM HKPD HKU IDABORT IDCANCEL IDIGNORE IDNO IDOK IDRETRY IDYES MB_ABORTRETRYIGNORE MB_DEFBUTTON1 MB_DEFBUTTON2 MB_DEFBUTTON3 MB_DEFBUTTON4 MB_ICONEXCLAMATION MB_ICONINFORMATION MB_ICONQUESTION MB_ICONSTOP MB_OK MB_OKCANCEL MB_RETRYCANCEL MB_RIGHT MB_SETFOREGROUND MB_TOPMOST MB_USERICON MB_YESNO MB_YESNOCANCEL NORMAL OFFLINE READONLY SET SHCTX SW_HIDE SW_SHOWMAXIMIZED SW_SHOWMINIMIZED SW_SHOWNORMAL SYSTEM TEMPORARY all auto both bottom bzip2 checkbox colored current false force hide ifdiff ifnewer lastused leave left listonly lzma nevershow none normal off on pop push radiobuttons right show silent silentlog smooth textonly top true try zlib"
""
"";
// color text
static SScintillaColors g_rgb_Syntax_nsis[] =
{ {} };

//--------------------------------
//---- oscript Language
//--------------------------------
// language
static CString g_str_oscript_language = _T("oscript");
// extentions
static CString g_str_oscript_extention = _T("oscript");
// comment line
static CString g_str_oscript_commentline = _T("//");
// comment start
static CString g_str_oscript_commentStart = _T("/*");
// comment end
static CString g_str_oscript_commentEnd = _T("*/");
// keywords
static const char* g_oscript_KeyWords =
"break breakif by case continue continueif default downto else elseif end for goto if in repeat switch to until while function return void dll inbyref inout linked nodebug super this xcmd xfcn"
"false true undefined booleantype bytestype datatype dynamictype errortype externtype integertype listtype longtype objecttype objreftype pointtype realtype scripttype stringtype undefinedtype voidtype"
"and eq ge gt le lt ne not or xor"
"assoc boolean bytes date dynamic error extern file integer list long object point real recarray record script string cachetree capiconnect capierr capilog capilogin compiler dapisession dapinode dapiversion dapistream filecopy fileprefs frame javaobject mailmessage pop3session smtpsession ssloptions patfind patchange regex socket sqlconnection sqlcursor uapisession uapiuser wapisession wapimap wapimaptask wapiwork wapisubwork domattr domcdatasection domcharacterdata domcomment domdocument domdocumentfragment domdocumenttype domelement domentity domentityreference domimplementation domnamednodemap domnode domnodelist domnotation domparser domprocessinginstruction domtext saxparser xslprocessor"
"datatypename echo echodebug echoerror echoinfo echostamp echowarn getfeatures isdefined iserror isfeature isinvokable isnoterror isnotset isobject isset isundefined length nparameters parameters pointh pointv type"
"cachetree capiconnect capierr capilog capilogin compiler dapisession dapinode dapiversion dapistream filecopy fileprefs frame javaobject mailmessage pop3session smtpsession ssloptions patfind patchange regex socket sqlconnection sqlcursor uapisession uapiuser wapisession wapimap wapimaptask wapiwork wapisubwork domattr domcdatasection domcharacterdata domcomment domdocument domdocumentfragment domdocumenttype domelement domentity domentityreference domimplementation domnamednodemap domnode domnodelist domnotation domparser domprocessinginstruction domtext saxparser xslprocessor"
"cachetree capiconnect capierr capilog capilogin compiler dapisession dapinode dapiversion dapistream filecopy fileprefs frame javaobject mailmessage pop3session smtpsession ssloptions patfind patchange regex socket sqlconnection sqlcursor uapisession uapiuser wapisession wapimap wapimaptask wapiwork wapisubwork domattr domcdatasection domcharacterdata domcomment domdocument domdocumentfragment domdocumenttype domelement domentity domentityreference domimplementation domnamednodemap domnode domnodelist domnotation domparser domprocessinginstruction domtext saxparser xslprocessor";
// color text
static SScintillaColors g_rgb_Syntax_oscript[] =
{ {} };

//--------------------------------
//---- objc Language
//--------------------------------
// language
static CString g_str_objc_language = _T("objc");
// extentions
static CString g_str_objc_extention = _T("objc");
// comment line
static CString g_str_objc_commentline = _T("//");
// comment start
static CString g_str_objc_commentStart = _T("/*");
// comment end
static CString g_str_objc_commentEnd = _T("*/");
// keywords
static const char* g_objc_KeyWords =
"if else switch case default break goto return for while do continue typedef sizeof NULL self super nil NIL"
"interface implementation protocol end private protected public class selector encode defs"
"void struct union enum char short int long double float signed unsigned const static extern auto register volatile id Class SEL IMP BOOL"
"oneway in out inout bycopy byref"
"oneway in out inout bycopy byref";
// color text
static SScintillaColors g_rgb_Syntax_objc[] =
{ {} };

//--------------------------------
//---- pascal Language
//--------------------------------
// language
static CString g_str_pascal_language = _T("pascal");
// extentions
static CString g_str_pascal_extention = _T("pascal");
// comment line
static CString g_str_pascal_commentline = _T("");
// comment start
static CString g_str_pascal_commentStart = _T("{");
// comment end
static CString g_str_pascal_commentEnd = _T("}");
// keywords
static const char* g_pascal_KeyWords =
"and array asm begin case cdecl class const constructor default destructor div do downto else end end. except exit exports external far file finalization finally for function goto if implementation in index inherited initialization inline interface label library message mod near nil not object of on or out overload override packed pascal private procedure program property protected public published raise read record register repeat resourcestring safecall set shl shr stdcall stored string then threadvar to try type unit until uses var virtual while with write xor"
"and array asm begin case cdecl class const constructor default destructor div do downto else end end. except exit exports external far file finalization finally for function goto if implementation in index inherited initialization inline interface label library message mod near nil not object of on or out overload override packed pascal private procedure program property protected public published raise read record register repeat resourcestring safecall set shl shr stdcall stored string then threadvar to try type unit until uses var virtual while with write xor";
// color text
static SScintillaColors g_rgb_Syntax_pascal[] =
{ {} };

//--------------------------------
//---- perl Language
//--------------------------------
// language
static CString g_str_perl_language = _T("perl");
// extentions
static CString g_str_perl_extention = _T("perl");
// comment line
static CString g_str_perl_commentline = _T("#");
// comment start
static CString g_str_perl_commentStart = _T("");
// comment end
static CString g_str_perl_commentEnd = _T("");
// keywords
static const char* g_perl_KeyWords =
"NULL __FILE__ __LINE__ __PACKAGE__ __DATA__ __END__ AUTOLOAD BEGIN CORE DESTROY END EQ GE GT INIT LE LT NE CHECK abs accept alarm and atan2 bind binmode bless caller chdir chmod chomp chop chown chr chroot close closedir cmp connect continue cos crypt dbmclose dbmopen defined delete die do dump each else elsif endgrent endhostent endnetent endprotoent endpwent endservent eof eq eval exec exists exit exp fcntl fileno flock for foreach fork format formline ge getc getgrent getgrgid getgrnam gethostbyaddr gethostbyname gethostent getlogin getnetbyaddr getnetbyname getnetent getpeername getpgrp getppid getpriority getprotobyname getprotobynumber getprotoent getpwent getpwnam getpwuid getservbyname getservbyport getservent getsockname getsockopt glob gmtime goto grep gt hex if index int ioctl join keys kill last lc lcfirst le length link listen local localtime lock log lstat lt m map mkdir msgctl msgget msgrcv msgsnd my ne next no not oct open opendir or ord our pack package pipe pop pos print printf prototype push q qq qr quotemeta qu qw qx rand read readdir readline readlink readpipe recv redo ref rename require reset return reverse rewinddir rindex rmdir s scalar seek seekdir select semctl semget semop send setgrent sethostent setnetent setpgrp setpriority setprotoent setpwent setservent setsockopt shift shmctl shmget shmread shmwrite shutdown sin sleep socket socketpair sort splice split sprintf sqrt srand stat study sub substr symlink syscall sysopen sysread sysseek system syswrite tell telldir tie tied time times tr truncate uc ucfirst umask undef unless unlink unpack unshift untie until use utime values vec wait waitpid wantarray warn while write x xor y"
"NULL __FILE__ __LINE__ __PACKAGE__ __DATA__ __END__ AUTOLOAD BEGIN CORE DESTROY END EQ GE GT INIT LE LT NE CHECK abs accept alarm and atan2 bind binmode bless caller chdir chmod chomp chop chown chr chroot close closedir cmp connect continue cos crypt dbmclose dbmopen defined delete die do dump each else elsif endgrent endhostent endnetent endprotoent endpwent endservent eof eq eval exec exists exit exp fcntl fileno flock for foreach fork format formline ge getc getgrent getgrgid getgrnam gethostbyaddr gethostbyname gethostent getlogin getnetbyaddr getnetbyname getnetent getpeername getpgrp getppid getpriority getprotobyname getprotobynumber getprotoent getpwent getpwnam getpwuid getservbyname getservbyport getservent getsockname getsockopt glob gmtime goto grep gt hex if index int ioctl join keys kill last lc lcfirst le length link listen local localtime lock log lstat lt m map mkdir msgctl msgget msgrcv msgsnd my ne next no not oct open opendir or ord our pack package pipe pop pos print printf prototype push q qq qr quotemeta qu qw qx rand read readdir readline readlink readpipe recv redo ref rename require reset return reverse rewinddir rindex rmdir s scalar seek seekdir select semctl semget semop send setgrent sethostent setnetent setpgrp setpriority setprotoent setpwent setservent setsockopt shift shmctl shmget shmread shmwrite shutdown sin sleep socket socketpair sort splice split sprintf sqrt srand stat study sub substr symlink syscall sysopen sysread sysseek system syswrite tell telldir tie tied time times tr truncate uc ucfirst umask undef unless unlink unpack unshift untie until use utime values vec wait waitpid wantarray warn while write x xor y";
// color text
static SScintillaColors g_rgb_Syntax_perl[] =
{ {} };

//--------------------------------
//---- php Language
//--------------------------------
// language
static CString g_str_php_language = _T("php");
// extentions
static CString g_str_php_extention = _T("php");
// comment line
static CString g_str_php_commentline = _T("//");
// comment start
static CString g_str_php_commentStart = _T("/*");
// comment end
static CString g_str_php_commentEnd = _T("*/");
// keywords
static const char* g_php_KeyWords =
"__autoload __class__ __compiler_halt_offset__ __construct __destruct __dir__ __file__ __function__ __halt_compiler __line__ __method__ __namespace__ __sleep __trait__ __wakeup _cookie _files _get _post abday_1 abday_2 abday_3 abday_4 abday_5 abday_6 abday_7 abmon_1 abmon_10 abmon_11 abmon_12 abmon_2 abmon_3 abmon_4 abmon_5 abmon_6 abmon_7 abmon_8 abmon_9 abs abstract acos acosh addcslashes addslashes af_inet af_inet6 af_unix al_bits al_buffer al_channels al_cone_inner_angle al_cone_outer_angle al_cone_outer_gain al_direction al_false al_format_mono16 al_format_mono8 al_format_stereo16 al_format_stereo8 al_frequency al_gain al_initial al_looping al_max_distance al_max_gain al_min_gain al_orientation al_paused al_pitch al_playing al_position al_reference_distance al_rolloff_factor al_size al_source_relative al_source_state al_stopped al_true al_velocity alc_frequency alc_refresh alc_sync alt_digits am_str and apache_child_terminate apache_get_modules apache_get_version apache_getenv apache_lookup_uri apache_map apache_note apache_request_headers apache_reset_timeout apache_response_headers apache_setenv apc_add apc_bin_dump apc_bin_dumpfile apc_bin_load apc_bin_loadfile apc_bin_verify_crc32 apc_bin_verify_md5 apc_cache_info apc_cas apc_clear_cache apc_compile_file apc_dec apc_define_constants apc_delete apc_delete_file apc_exists apc_fetch apc_inc apc_iter_all apc_iter_atime apc_iter_ctime apc_iter_device apc_iter_dtime apc_iter_filename apc_iter_inode apc_iter_key apc_iter_md5 apc_iter_mem_size apc_iter_mtime apc_iter_none apc_iter_num_hits apc_iter_refcount apc_iter_ttl apc_iter_type apc_iter_value apc_list_active apc_list_deleted apc_load_constants apc_sma_info apc_store apd_breakpoint apd_callstack apd_clunk apd_continue apd_croak apd_dump_function_table apd_dump_persistent_resources apd_dump_regular_resources apd_echo apd_get_active_symbols apd_set_pprof_trace apd_set_session apd_set_session_trace apd_set_session_trace_socket apd_version args_trace array array_change_key_case array_chunk array_column array_combine array_count_values array_diff array_diff_assoc array_diff_key array_diff_uassoc array_diff_ukey array_fill array_fill_keys array_filter array_filter_use_both array_filter_use_key array_flip array_intersect array_intersect_assoc array_intersect_key array_intersect_uassoc array_intersect_ukey array_key_exists array_keys array_map array_merge array_merge_recursive array_multisort array_pad array_pop array_product array_push array_rand array_reduce array_replace array_replace_recursive array_reverse array_search array_shift array_slice array_sort array_splice array_sum array_udiff array_udiff_assoc array_udiff_uassoc array_uintersect array_uintersect_assoc array_uintersect_uassoc array_unique array_unshift array_values array_walk array_walk_recursive arrayaccess arrayiterator arrayobject arsort as asin asinh asort assert assert_active assert_bail assert_callback assert_options assert_quiet_eval assert_warning assignment_trace atan atan2 atanh base64_decode base64_encode base_convert basename bbcode_add_element bbcode_add_smiley bbcode_arg_double_quote bbcode_arg_html_quote bbcode_arg_quote_escaping bbcode_arg_single_quote bbcode_auto_correct bbcode_correct_reopen_tags bbcode_create bbcode_default_smileys_off bbcode_default_smileys_on bbcode_destroy bbcode_disable_tree_build bbcode_flags_arg_parsing bbcode_flags_cdata_not_allowed bbcode_flags_deny_reopen_child bbcode_flags_one_open_per_level bbcode_flags_remove_if_empty bbcode_flags_smileys_off bbcode_flags_smileys_on bbcode_force_smileys_off bbcode_parse bbcode_set_arg_parser bbcode_set_flags bbcode_set_flags_add bbcode_set_flags_remove bbcode_set_flags_set bbcode_smileys_case_insensitive bbcode_type_arg bbcode_type_noarg bbcode_type_optarg bbcode_type_root bbcode_type_single bcadd bccomp bcdiv bcmod bcmul bcompiler_load bcompiler_load_exe bcompiler_parse_class bcompiler_read bcompiler_write_class bcompiler_write_constant bcompiler_write_exe_footer bcompiler_write_file bcompiler_write_footer bcompiler_write_function bcompiler_write_functions_from_file bcompiler_write_header bcompiler_write_included_filename bcpow bcpowmod bcscale bcsqrt bcsub bin2hex bind_textdomain_codeset bindec bindtextdomain blenc_encrypt blenc_ext_version bool boolean boolval break bson_decode bson_encode bus_adraln bus_adrerr bus_objerr bzclose bzcompress bzdecompress bzerrno bzerror bzerrstr bzflush bzopen bzread bzwrite cairo_antialias_default cairo_antialias_gray cairo_antialias_none cairo_antialias_subpixel cairo_content_alpha cairo_content_color cairo_content_color_alpha cairo_create cairo_extend_none cairo_extend_pad cairo_extend_reflect cairo_extend_repeat cairo_fill_rule_even_odd cairo_fill_rule_winding cairo_filter_best cairo_filter_bilinear cairo_filter_fast cairo_filter_gaussian cairo_filter_good cairo_filter_nearest cairo_font_face_get_type cairo_font_face_status cairo_font_options_create cairo_font_options_equal cairo_font_options_get_antialias cairo_font_options_get_hint_metrics cairo_font_options_get_hint_style cairo_font_options_get_subpixel_order cairo_font_options_hash cairo_font_options_merge cairo_font_options_set_antialias cairo_font_options_set_hint_metrics cairo_font_options_set_hint_style cairo_font_options_set_subpixel_order cairo_font_options_status cairo_font_slant_italic cairo_font_slant_normal cairo_font_slant_oblique cairo_font_type_ft cairo_font_type_quartz cairo_font_type_toy cairo_font_type_win32 cairo_font_weight_bold cairo_font_weight_normal cairo_format_a1 cairo_format_a8 cairo_format_argb32 cairo_format_rgb24 cairo_format_stride_for_width cairo_hint_metrics_default cairo_hint_metrics_off cairo_hint_metrics_on cairo_hint_style_default cairo_hint_style_full cairo_hint_style_medium cairo_hint_style_none cairo_hint_style_slight cairo_image_surface_create cairo_image_surface_create_for_data cairo_image_surface_create_from_png cairo_image_surface_get_data cairo_image_surface_get_format cairo_image_surface_get_height cairo_image_surface_get_stride cairo_image_surface_get_width cairo_line_cap_butt cairo_line_cap_round cairo_line_cap_square cairo_line_join_bevel cairo_line_join_miter cairo_line_join_round cairo_matrix_create_scale cairo_matrix_create_translate cairo_matrix_invert cairo_matrix_multiply cairo_matrix_rotate cairo_matrix_transform_distance cairo_matrix_transform_point cairo_matrix_translate cairo_operator_add cairo_operator_atop cairo_operator_clear cairo_operator_dest cairo_operator_dest_atop cairo_operator_dest_in cairo_operator_dest_out cairo_operator_dest_over cairo_operator_in cairo_operator_out cairo_operator_over cairo_operator_saturate cairo_operator_source cairo_operator_xor cairo_pattern_add_color_stop_rgb cairo_pattern_add_color_stop_rgba cairo_pattern_create_for_surface cairo_pattern_create_linear cairo_pattern_create_radial cairo_pattern_create_rgb cairo_pattern_create_rgba cairo_pattern_get_color_stop_count cairo_pattern_get_color_stop_rgba cairo_pattern_get_extend cairo_pattern_get_filter cairo_pattern_get_linear_points cairo_pattern_get_matrix cairo_pattern_get_radial_circles cairo_pattern_get_rgba cairo_pattern_get_surface cairo_pattern_get_type cairo_pattern_set_extend cairo_pattern_set_filter cairo_pattern_set_matrix cairo_pattern_status cairo_pattern_type_linear cairo_pattern_type_radial cairo_pattern_type_solid cairo_pattern_type_surface cairo_pdf_surface_create cairo_pdf_surface_set_size cairo_ps_get_levels cairo_ps_level_2 cairo_ps_level_3 cairo_ps_level_to_string cairo_ps_surface_create cairo_ps_surface_dsc_begin_page_setup cairo_ps_surface_dsc_begin_setup cairo_ps_surface_dsc_comment cairo_ps_surface_get_eps cairo_ps_surface_restrict_to_level cairo_ps_surface_set_eps cairo_ps_surface_set_size cairo_scaled_font_create cairo_scaled_font_extents cairo_scaled_font_get_ctm cairo_scaled_font_get_font_face cairo_scaled_font_get_font_matrix cairo_scaled_font_get_font_options cairo_scaled_font_get_scale_matrix cairo_scaled_font_get_type cairo_scaled_font_glyph_extents cairo_scaled_font_status cairo_scaled_font_text_extents cairo_status_clip_not_representable cairo_status_file_not_found cairo_status_invalid_content cairo_status_invalid_dash cairo_status_invalid_dsc_comment cairo_status_invalid_format cairo_status_invalid_index cairo_status_invalid_matrix cairo_status_invalid_path_data cairo_status_invalid_pop_group cairo_status_invalid_restore cairo_status_invalid_status cairo_status_invalid_stride cairo_status_invalid_string cairo_status_invalid_visual cairo_status_no_current_point cairo_status_no_memory cairo_status_null_pointer cairo_status_pattern_type_mismatch cairo_status_read_error cairo_status_success cairo_status_surface_finished cairo_status_surface_type_mismatch cairo_status_temp_file_error cairo_status_write_error cairo_subpixel_order_bgr cairo_subpixel_order_default cairo_subpixel_order_rgb cairo_subpixel_order_vbgr cairo_subpixel_order_vrgb cairo_surface_copy_page cairo_surface_create_similar cairo_surface_finish cairo_surface_flush cairo_surface_get_content cairo_surface_get_device_offset cairo_surface_get_font_options cairo_surface_get_type cairo_surface_mark_dirty cairo_surface_mark_dirty_rectangle cairo_surface_set_device_offset cairo_surface_set_fallback_resolution cairo_surface_show_page cairo_surface_status cairo_surface_type_beos cairo_surface_type_directfb cairo_surface_type_glitz cairo_surface_type_image cairo_surface_type_os2 cairo_surface_type_pdf cairo_surface_type_ps cairo_surface_type_quartz cairo_surface_type_quartz_image cairo_surface_type_svg cairo_surface_type_win32 cairo_surface_type_win32_printing cairo_surface_type_xcb cairo_surface_type_xlib cairo_surface_write_to_png cairo_svg_surface_create cairo_svg_surface_restrict_to_version cairo_svg_version_1_1 cairo_svg_version_1_2
 cairo_svg_version_to_string cal_days_in_month cal_dow_dayno cal_dow_long cal_dow_short cal_easter_always_gregorian cal_easter_always_julian cal_easter_default cal_easter_roman cal_french cal_from_jd cal_gregorian cal_info cal_jewish cal_jewish_add_alafim cal_jewish_add_alafim_geresh cal_jewish_add_gereshayim cal_julian cal_month_french cal_month_gregorian_long cal_month_gregorian_short cal_month_jewish cal_month_julian_long cal_month_julian_short cal_num_cals cal_to_jd calcul_hmac calculhmac call_user_func call_user_func_array call_user_method call_user_method_array callable case case_lower case_upper catch ceil cfunction char_max chdb_create chdir checkdate checkdnsrr chgrp chmod chop chown chr chroot chunk_split cl_expunge class class_alias class_exists class_implements class_parents class_uses cld_continued cld_dumped cld_exited cld_killed cld_stopped cld_trapped clearstatcache cli_get_process_title cli_set_process_title clone closedir closelog clsctx_all clsctx_inproc_handler clsctx_inproc_server clsctx_local_server clsctx_remote_server clsctx_server codeset collator_asort collator_compare collator_create collator_get_attribute collator_get_error_code collator_get_error_message collator_get_locale collator_get_sort_key collator_get_strength collator_set_attribute collator_set_strength collator_sort collator_sort_with_sort_keys com_create_guid com_event_sink com_get com_get_active_object com_invoke com_load com_load_typelib com_message_pump com_print_typeinfo com_propget com_propput com_set compact connection_aborted connection_normal connection_status connection_timeout const constant continue convert_cyr_string convert_uudecode convert_uuencode copy cos cosh count count_chars count_normal count_recursive cp_acp cp_maccp cp_move cp_oemcp cp_symbol cp_thread_acp cp_uid cp_utf7 cp_utf8 crc32 create_function credits_all credits_docs credits_fullpage credits_general credits_group credits_modules credits_qa credits_sapi crncystr crypt crypt_blowfish crypt_ext_des crypt_md5 crypt_salt_length crypt_sha256 crypt_sha512 crypt_std_des ctype_alnum ctype_alpha ctype_cntrl ctype_digit ctype_graph ctype_lower ctype_print ctype_punct ctype_space ctype_upper ctype_xdigit cubrid_affected_rows cubrid_assoc cubrid_async cubrid_autocommit_false cubrid_autocommit_true cubrid_bind cubrid_both cubrid_client_encoding cubrid_close cubrid_close_prepare cubrid_close_request cubrid_col_get cubrid_col_size cubrid_column_names cubrid_column_types cubrid_commit cubrid_connect cubrid_connect_with_url cubrid_current_oid cubrid_cursor_current cubrid_cursor_error cubrid_cursor_first cubrid_cursor_last cubrid_cursor_success cubrid_data_seek cubrid_db_name cubrid_disconnect cubrid_drop cubrid_errno cubrid_error cubrid_error_code cubrid_error_code_facility cubrid_error_msg cubrid_exec_query_all cubrid_execute cubrid_facility_cas cubrid_facility_cci cubrid_facility_client cubrid_facility_dbms cubrid_fetch cubrid_fetch_array cubrid_fetch_assoc cubrid_fetch_field cubrid_fetch_lengths cubrid_fetch_object cubrid_fetch_row cubrid_field_flags cubrid_field_len cubrid_field_name cubrid_field_seek cubrid_field_table cubrid_field_type cubrid_free_result cubrid_get cubrid_get_autocommit cubrid_get_charset cubrid_get_class_name cubrid_get_client_info cubrid_get_db_parameter cubrid_get_query_timeout cubrid_get_server_info cubrid_include_oid cubrid_insert_id cubrid_is_instance cubrid_list_dbs cubrid_lob cubrid_lob2_bind cubrid_lob2_close cubrid_lob2_export cubrid_lob2_import cubrid_lob2_new cubrid_lob2_read cubrid_lob2_seek cubrid_lob2_seek64 cubrid_lob2_size cubrid_lob2_size64 cubrid_lob2_tell cubrid_lob2_tell64 cubrid_lob2_write cubrid_lob_close cubrid_lob_export cubrid_lob_get cubrid_lob_send cubrid_lob_size cubrid_lock_read cubrid_lock_write cubrid_move_cursor cubrid_next_result cubrid_no_more_data cubrid_num cubrid_num_cols cubrid_num_fields cubrid_num_rows cubrid_object cubrid_param_isolation_level cubrid_param_lock_timeout cubrid_pconnect cubrid_pconnect_with_url cubrid_ping cubrid_prepare cubrid_put cubrid_query cubrid_real_escape_string cubrid_result cubrid_rollback cubrid_sch_attr_privilege cubrid_sch_attribute cubrid_sch_class cubrid_sch_class_attribute cubrid_sch_class_method cubrid_sch_class_privilege cubrid_sch_constraint cubrid_sch_cross_reference cubrid_sch_direct_super_class cubrid_sch_exported_keys cubrid_sch_imported_keys cubrid_sch_method cubrid_sch_method_file cubrid_sch_primary_key cubrid_sch_query_spec cubrid_sch_subclass cubrid_sch_superclass cubrid_sch_trigger cubrid_sch_vclass cubrid_schema cubrid_seq_drop cubrid_seq_insert cubrid_seq_put cubrid_set_add cubrid_set_autocommit cubrid_set_db_parameter cubrid_set_drop cubrid_set_query_timeout cubrid_unbuffered_query cubrid_version curl_close curl_copy_handle curl_errno curl_error curl_escape curl_exec curl_file_create curl_fnmatchfunc_fail curl_fnmatchfunc_match curl_fnmatchfunc_nomatch curl_getinfo curl_http_version_1_0 curl_http_version_1_1 curl_http_version_2_0 curl_http_version_none curl_init curl_ipresolve_v4 curl_ipresolve_v6 curl_ipresolve_whatever curl_lock_data_cookie curl_lock_data_dns curl_lock_data_ssl_session curl_multi_add_handle curl_multi_close curl_multi_exec curl_multi_getcontent curl_multi_info_read curl_multi_init curl_multi_remove_handle curl_multi_select curl_multi_setopt curl_multi_strerror curl_netrc_ignored curl_netrc_optional curl_netrc_required curl_pause curl_readfunc_pause curl_reset curl_rtspreq_announce curl_rtspreq_describe curl_rtspreq_get_parameter curl_rtspreq_options curl_rtspreq_pause curl_rtspreq_play curl_rtspreq_receive curl_rtspreq_record curl_rtspreq_set_parameter curl_rtspreq_setup curl_rtspreq_teardown curl_setopt curl_setopt_array curl_share_close curl_share_init curl_share_setopt curl_sslversion_default curl_sslversion_sslv2 curl_sslversion_sslv3 curl_sslversion_tlsv1 curl_sslversion_tlsv1_0 curl_sslversion_tlsv1_1 curl_sslversion_tlsv1_2 curl_strerror curl_timecond_ifmodsince curl_timecond_ifunmodsince curl_timecond_lastmod curl_timecond_none curl_tlsauth_srp curl_unescape curl_version curl_version_http2 curl_version_ipv6 curl_version_kerberos4 curl_version_libz curl_version_ssl curl_wrappers_enabled curl_writefunc_pause curlauth_any curlauth_anysafe curlauth_basic curlauth_digest curlauth_digest_ie curlauth_gssnegotiate curlauth_none curlauth_ntlm curlauth_only curlclosepolicy_callback curlclosepolicy_least_recently_used curlclosepolicy_least_traffic curlclosepolicy_oldest curlclosepolicy_slowest curle_aborted_by_callback curle_bad_calling_order curle_bad_content_encoding curle_bad_download_resume curle_bad_function_argument curle_bad_password_entered curle_couldnt_connect curle_couldnt_resolve_host curle_couldnt_resolve_proxy curle_failed_init curle_file_couldnt_read_file curle_filesize_exceeded curle_ftp_access_denied curle_ftp_bad_download_resume curle_ftp_cant_get_host curle_ftp_cant_reconnect curle_ftp_couldnt_get_size curle_ftp_couldnt_retr_file curle_ftp_couldnt_set_ascii curle_ftp_couldnt_set_binary curle_ftp_couldnt_stor_file curle_ftp_couldnt_use_rest curle_ftp_partial_file curle_ftp_port_failed curle_ftp_quote_error curle_ftp_ssl_failed curle_ftp_user_password_incorrect curle_ftp_weird_227_format curle_ftp_weird_pass_reply curle_ftp_weird_pasv_reply curle_ftp_weird_server_reply curle_ftp_weird_user_reply curle_ftp_write_error curle_function_not_found curle_got_nothing curle_http_not_found curle_http_port_failed curle_http_post_error curle_http_range_error curle_http_returned_error curle_ldap_cannot_bind curle_ldap_invalid_url curle_ldap_search_failed curle_library_not_found curle_malformat_user curle_obsolete curle_ok curle_operation_timedout curle_operation_timeouted curle_out_of_memory curle_partial_file curle_read_error curle_recv_error curle_send_error curle_share_in_use curle_ssh curle_ssl_cacert curle_ssl_certproblem curle_ssl_cipher curle_ssl_connect_error curle_ssl_engine_notfound curle_ssl_engine_setfailed curle_ssl_peer_certificate curle_telnet_option_syntax curle_too_many_redirects curle_unknown_telnet_option curle_unsupported_protocol curle_url_malformat curle_url_malformat_user curle_write_error curlftpauth_default curlftpauth_ssl curlftpauth_tls curlftpmethod_multicwd curlftpmethod_nocwd curlftpmethod_singlecwd curlftpssl_all curlftpssl_ccc_active curlftpssl_ccc_none curlftpssl_ccc_passive curlftpssl_control curlftpssl_none curlftpssl_try curlgssapi_delegation_flag curlgssapi_delegation_policy_flag curlinfo_appconnect_time curlinfo_certinfo curlinfo_condition_unmet curlinfo_connect_time curlinfo_content_length_download curlinfo_content_length_upload curlinfo_content_type curlinfo_cookielist curlinfo_effective_url curlinfo_filetime curlinfo_ftp_entry_path curlinfo_header_out curlinfo_header_size curlinfo_http_code curlinfo_http_connectcode curlinfo_httpauth_avail curlinfo_lastone curlinfo_local_ip curlinfo_local_port curlinfo_namelookup_time curlinfo_num_connects curlinfo_os_errno curlinfo_pretransfer_time curlinfo_primary_ip curlinfo_primary_port curlinfo_private curlinfo_proxyauth_avail curlinfo_redirect_count curlinfo_redirect_time curlinfo_redirect_url curlinfo_request_size curlinfo_response_code curlinfo_rtsp_client_cseq curlinfo_rtsp_cseq_recv curlinfo_rtsp_server_cseq curlinfo_rtsp_session_id curlinfo_size_download curlinfo_size_upload curlinfo_speed_download curlinfo_speed_upload curlinfo_ssl_engines curlinfo_ssl_verifyresult curlinfo_starttransfer_time curlinfo_total_time curlm_bad_easy_handle curlm_bad_handle curlm_call_multi_perform curlm_internal_error curlm_ok curlm_out_of_memory curlmopt_maxconnects curlmopt_pipelining curlmsg_done curlopt_accept_encoding curlopt_accepttimeout_ms curlopt_address_scope curlopt_append curlopt_autoreferer curlopt_binarytransfer curlopt_buffersize curlopt_cainfo
 curlopt_capath curlopt_certinfo curlopt_closepolicy curlopt_connect_only curlopt_connecttimeout curlopt_connecttimeout_ms curlopt_cookie curlopt_cookiefile curlopt_cookiejar curlopt_cookielist curlopt_cookiesession curlopt_crlf curlopt_crlfile curlopt_customrequest curlopt_dirlistonly curlopt_dns_cache_timeout curlopt_dns_servers curlopt_dns_use_global_cache curlopt_egdsocket curlopt_encoding curlopt_failonerror curlopt_file curlopt_filetime curlopt_fnmatch_function curlopt_followlocation curlopt_forbid_reuse curlopt_fresh_connect curlopt_ftp_account curlopt_ftp_alternative_to_user curlopt_ftp_create_missing_dirs curlopt_ftp_filemethod curlopt_ftp_response_timeout curlopt_ftp_skip_pasv_ip curlopt_ftp_ssl curlopt_ftp_ssl_ccc curlopt_ftp_use_eprt curlopt_ftp_use_epsv curlopt_ftp_use_pret curlopt_ftpappend curlopt_ftpascii curlopt_ftplistonly curlopt_ftpport curlopt_ftpsslauth curlopt_gssapi_delegation curlopt_header curlopt_headerfunction curlopt_http200aliases curlopt_http_content_decoding curlopt_http_transfer_decoding curlopt_http_version curlopt_httpauth curlopt_httpget curlopt_httpheader curlopt_httpproxytunnel curlopt_ignore_content_length curlopt_infile curlopt_infilesize curlopt_interface curlopt_ipresolve curlopt_issuercert curlopt_keypasswd curlopt_krb4level curlopt_krblevel curlopt_localport curlopt_localportrange curlopt_low_speed_limit curlopt_low_speed_time curlopt_mail_auth curlopt_mail_from curlopt_mail_rcpt curlopt_max_recv_speed_large curlopt_max_send_speed_large curlopt_maxconnects curlopt_maxfilesize curlopt_maxredirs curlopt_mute curlopt_netrc curlopt_netrc_file curlopt_new_directory_perms curlopt_new_file_perms curlopt_nobody curlopt_noprogress curlopt_noproxy curlopt_nosignal curlopt_passwdfunction curlopt_password curlopt_port curlopt_post curlopt_postfields curlopt_postquote curlopt_postredir curlopt_prequote curlopt_private curlopt_progressfunction curlopt_protocols curlopt_proxy curlopt_proxy_transfer_mode curlopt_proxyauth curlopt_proxypassword curlopt_proxyport curlopt_proxytype curlopt_proxyusername curlopt_proxyuserpwd curlopt_put curlopt_quote curlopt_random_file curlopt_range curlopt_readdata curlopt_readfunction curlopt_redir_protocols curlopt_referer curlopt_resolve curlopt_resume_from curlopt_returntransfer curlopt_rtsp_client_cseq curlopt_rtsp_request curlopt_rtsp_server_cseq curlopt_rtsp_session_id curlopt_rtsp_stream_uri curlopt_rtsp_transport curlopt_safe_upload curlopt_share curlopt_socks5_gssapi_nec curlopt_socks5_gssapi_service curlopt_ssh_auth_types curlopt_ssh_host_public_key_md5 curlopt_ssh_knownhosts curlopt_ssh_private_keyfile curlopt_ssh_public_keyfile curlopt_ssl_cipher_list curlopt_ssl_options curlopt_ssl_sessionid_cache curlopt_ssl_verifyhost curlopt_ssl_verifypeer curlopt_sslcert curlopt_sslcertpasswd curlopt_sslcerttype curlopt_sslengine curlopt_sslengine_default curlopt_sslkey curlopt_sslkeypasswd curlopt_sslkeytype curlopt_sslversion curlopt_stderr curlopt_tcp_keepalive curlopt_tcp_keepidle curlopt_tcp_keepintvl curlopt_tcp_nodelay curlopt_telnetoptions curlopt_tftp_blksize curlopt_timecondition curlopt_timeout curlopt_timeout_ms curlopt_timevalue curlopt_tlsauth_password curlopt_tlsauth_type curlopt_tlsauth_username curlopt_transfer_encoding curlopt_transfertext curlopt_unrestricted_auth curlopt_upload curlopt_url curlopt_use_ssl curlopt_useragent curlopt_username curlopt_userpwd curlopt_verbose curlopt_wildcardmatch curlopt_writefunction curlopt_writeheader curlpause_all curlpause_cont curlpause_recv curlpause_recv_cont curlpause_send curlpause_send_cont curlproto_all curlproto_dict curlproto_file curlproto_ftp curlproto_ftps curlproto_gopher curlproto_http curlproto_https curlproto_imap curlproto_imaps curlproto_ldap curlproto_ldaps curlproto_pop3 curlproto_pop3s curlproto_rtmp curlproto_rtmpe curlproto_rtmps curlproto_rtmpt curlproto_rtmpte curlproto_rtmpts curlproto_rtsp curlproto_scp curlproto_sftp curlproto_smtp curlproto_smtps curlproto_telnet curlproto_tftp curlproxy_http curlproxy_socks4 curlproxy_socks4a curlproxy_socks5 curlproxy_socks5_hostname curlshopt_none curlshopt_share curlshopt_unshare curlssh_auth_any curlssh_auth_default curlssh_auth_host curlssh_auth_keyboard curlssh_auth_none curlssh_auth_password curlssh_auth_publickey curlsslopt_allow_beast curlusessl_all curlusessl_control curlusessl_none curlusessl_try curlversion_now currency_symbol current cyrus_authenticate cyrus_bind cyrus_callback_noliteral cyrus_callback_numbered cyrus_close cyrus_conn_initialresponse cyrus_conn_nonsyncliteral cyrus_connect cyrus_query cyrus_unbind d_fmt d_t_fmt date date_add date_atom date_cookie date_create date_create_from_format date_create_immutable date_create_immutable_from_format date_date_set date_default_timezone_get date_default_timezone_set date_diff date_format date_get_last_errors date_interval_create_from_date_string date_interval_format date_iso8601 date_isodate_set date_modify date_offset_get date_parse date_parse_from_format date_rfc1036 date_rfc1123 date_rfc2822 date_rfc3339 date_rfc822 date_rfc850 date_rss date_sub date_sun_info date_sunrise date_sunset date_time_set date_timestamp_get date_timestamp_set date_timezone_get date_timezone_set date_w3c datefmt_create datefmt_format datefmt_get_calendar datefmt_get_datetype datefmt_get_error_code datefmt_get_error_message datefmt_get_locale datefmt_get_pattern datefmt_get_timetype datefmt_get_timezone_id datefmt_is_lenient datefmt_localtime datefmt_parse datefmt_set_calendar datefmt_set_lenient datefmt_set_pattern datefmt_set_timezone_id day_1 day_2 day_3 day_4 day_5 day_6 day_7 db2_autocommit db2_autocommit_off db2_autocommit_on db2_binary db2_bind_param db2_case_lower db2_case_natural db2_case_upper db2_char db2_client_info db2_close db2_column_privileges db2_columns db2_commit db2_conn_error db2_conn_errormsg db2_connect db2_convert db2_cursor_type db2_deferred_prepare_off db2_deferred_prepare_on db2_double db2_escape_string db2_exec db2_execute db2_fetch_array db2_fetch_assoc db2_fetch_both db2_fetch_object db2_fetch_row db2_field_display_size db2_field_name db2_field_num db2_field_precision db2_field_scale db2_field_type db2_field_width db2_foreign_keys db2_forward_only db2_free_result db2_free_stmt db2_get_option db2_last_insert_id db2_lob_read db2_long db2_next_result db2_num_fields db2_num_rows db2_param_file db2_param_in db2_param_inout db2_param_out db2_passthru db2_pclose db2_pconnect db2_prepare db2_primary_keys db2_procedure_columns db2_procedures db2_result db2_rollback db2_scrollable db2_server_info db2_set_option db2_special_columns db2_statistics db2_stmt_error db2_stmt_errormsg db2_table_privileges db2_tables dba_close dba_delete dba_exists dba_fetch dba_firstkey dba_handlers dba_insert dba_key_split dba_list dba_nextkey dba_open dba_optimize dba_popen dba_replace dba_sync dbase_add_record dbase_close dbase_create dbase_delete_record dbase_get_header_info dbase_get_record dbase_get_record_with_names dbase_numfields dbase_numrecords dbase_open dbase_pack dbase_replace_record dbplus_add dbplus_aql dbplus_chdir dbplus_close dbplus_curr dbplus_err_close dbplus_err_corrupt_tuple dbplus_err_crc dbplus_err_create dbplus_err_dbparse dbplus_err_dbpreexit dbplus_err_dbrunerr dbplus_err_duplicate dbplus_err_empty dbplus_err_eoscan dbplus_err_fifo dbplus_err_length dbplus_err_locked dbplus_err_lseek dbplus_err_magic dbplus_err_malloc dbplus_err_nidx dbplus_err_noerr dbplus_err_nolock dbplus_err_nusers dbplus_err_ontrap dbplus_err_open dbplus_err_panic dbplus_err_perm dbplus_err_pgsize dbplus_err_pipe dbplus_err_preexit dbplus_err_preproc dbplus_err_read dbplus_err_restricted dbplus_err_tcl dbplus_err_unknown dbplus_err_user dbplus_err_version dbplus_err_wait dbplus_err_warning0 dbplus_err_wlocked dbplus_err_wopen dbplus_err_write dbplus_errcode dbplus_errno dbplus_find dbplus_first dbplus_flush dbplus_freealllocks dbplus_freelock dbplus_freerlocks dbplus_getlock dbplus_getunique dbplus_info dbplus_last dbplus_lockrel dbplus_next dbplus_open dbplus_prev dbplus_rchperm dbplus_rcreate dbplus_rcrtexact dbplus_rcrtlike dbplus_resolve dbplus_restorepos dbplus_rkeys dbplus_ropen dbplus_rquery dbplus_rrename dbplus_rsecindex dbplus_runlink dbplus_rzap dbplus_savepos dbplus_setindex dbplus_setindexbynumber dbplus_sql dbplus_tcl dbplus_tremove dbplus_undo dbplus_undoprepare dbplus_unlockrel dbplus_unselect dbplus_update dbplus_xlockrel dbplus_xunlockrel dbx_close dbx_cmp_asc dbx_cmp_desc dbx_cmp_native dbx_cmp_number dbx_cmp_text dbx_colnames_lowercase dbx_colnames_unchanged dbx_colnames_uppercase dbx_compare dbx_connect dbx_error dbx_escape_string dbx_fbsql dbx_fetch_row dbx_mssql dbx_mysql dbx_oci8 dbx_odbc dbx_persistent dbx_pgsql dbx_query dbx_result_assoc dbx_result_index dbx_result_info dbx_result_unbuffered dbx_sort dbx_sqlite dbx_sybasect dcgettext dcngettext debug_backtrace debug_backtrace_ignore_args debug_backtrace_provide_object debug_print_backtrace debug_zval_dump decbin dechex decimal_point declare decoct default default_include_path define define_syslog_variables defined deg2rad delete dgettext die dio_close dio_fcntl dio_open dio_read dio_seek dio_stat dio_tcsetattr dio_truncate dio_write dir directory directory_separator dirname disk_free_space disk_total_space diskfreespace disp_e_badindex disp_e_divbyzero disp_e_overflow dl dngettext dns_a dns_a6 dns_aaaa dns_all dns_any dns_check_record dns_cname dns_get_mx dns_get_record dns_hinfo dns_mx dns_naptr dns_ns dns_ptr dns_soa dns_srv dns_txt do dom_hierarchy_request_err dom_import_simplexml dom_index_size_err dom_inuse_attribute_err dom_invalid_access_err dom_invalid_character_err dom_invalid_modification_err dom_invalid_state_err dom_namespace_err dom_no_data_allowed_err dom_no_modification_allowed_err dom_not_found_err
 dom_not_supported_err dom_php_err dom_syntax_err dom_validation_err dom_wrong_document_err domstring_size_err double doubleval e_all e_compile_error e_compile_warning e_core_error e_core_warning e_deprecated e_error e_notice e_parse e_recoverable_error e_strict e_user_deprecated e_user_error e_user_notice e_user_warning e_warning each easter_date easter_days echo eio_busy eio_cancel eio_chmod eio_chown eio_close eio_custom eio_dt_blk eio_dt_chr eio_dt_cmp eio_dt_dir eio_dt_door eio_dt_fifo eio_dt_lnk eio_dt_max eio_dt_mpb eio_dt_mpc eio_dt_nam eio_dt_nwk eio_dt_reg eio_dt_sock eio_dt_unknown eio_dt_wht eio_dup2 eio_event_loop eio_falloc_fl_keep_size eio_fallocate eio_fchmod eio_fchown eio_fdatasync eio_fstat eio_fstatvfs eio_fsync eio_ftruncate eio_futime eio_get_event_stream eio_get_last_error eio_grp eio_grp_add eio_grp_cancel eio_grp_limit eio_init eio_link eio_lstat eio_mkdir eio_mknod eio_nop eio_npending eio_nready eio_nreqs eio_nthreads eio_o_append eio_o_creat eio_o_excl eio_o_fsync eio_o_nonblock eio_o_rdonly eio_o_rdwr eio_o_trunc eio_o_wronly eio_open eio_poll eio_pri_default eio_pri_max eio_pri_min eio_read eio_readahead eio_readdir eio_readdir_dents eio_readdir_dirs_first eio_readdir_found_unknown eio_readdir_stat_order eio_readlink eio_realpath eio_rename eio_rmdir eio_s_ifblk eio_s_ifchr eio_s_ififo eio_s_ifreg eio_s_ifsock eio_s_irgrp eio_s_iroth eio_s_irusr eio_s_iwgrp eio_s_iwoth eio_s_iwusr eio_s_ixgrp eio_s_ixoth eio_s_ixusr eio_seek eio_seek_cur eio_seek_end eio_seek_set eio_sendfile eio_set_max_idle eio_set_max_parallel eio_set_max_poll_reqs eio_set_max_poll_time eio_set_min_parallel eio_stat eio_statvfs eio_symlink eio_sync eio_sync_file_range eio_sync_file_range_wait_after eio_sync_file_range_wait_before eio_sync_file_range_write eio_syncfs eio_truncate eio_unlink eio_utime eio_write else elseif empty enc7bit enc8bit encbase64 encbinary encother encquotedprintable end enddeclare endfor endforeach endif endswitch endwhile ent_compat ent_disallowed ent_html401 ent_html5 ent_ignore ent_noquotes ent_quotes ent_substitute ent_xhtml ent_xml1 era era_d_fmt era_d_t_fmt era_t_fmt era_year ereg ereg_replace eregi eregi_replace error_clear_last error_get_last error_log error_reporting error_trace escapeshellarg escapeshellcmd ev_persist ev_read ev_signal ev_timeout ev_write eval event_add event_base_free event_base_loop event_base_loopbreak event_base_loopexit event_base_new event_base_priority_init event_base_reinit event_base_set event_buffer_base_set event_buffer_disable event_buffer_enable event_buffer_fd_set event_buffer_free event_buffer_new event_buffer_priority_set event_buffer_read event_buffer_set_callback event_buffer_timeout_set event_buffer_watermark_set event_buffer_write event_del event_free event_new event_priority_set event_set event_timer_add event_timer_del event_timer_new event_timer_set evloop_nonblock evloop_once exec exif_imagetype exif_read_data exif_tagname exif_thumbnail exif_use_mbstring exit exp exp_eof exp_exact exp_fullbuffer exp_glob exp_regexp exp_timeout expect_expectl expect_popen explode expm1 extends extension_loaded extr_if_exists extr_overwrite extr_prefix_all extr_prefix_if_exists extr_prefix_invalid extr_prefix_same extr_refs extr_skip extract ezmlm_hash f_dupfd f_getfd f_getfl f_getlk f_getown f_rdlck f_setfl f_setlk f_setlkw f_setown f_unlck f_wrlck false fann_cascadetrain_on_data fann_cascadetrain_on_file fann_clear_scaling_params fann_copy fann_cos fann_cos_symmetric fann_create_from_file fann_create_shortcut fann_create_shortcut_array fann_create_sparse fann_create_sparse_array fann_create_standard fann_create_standard_array fann_create_train fann_create_train_from_callback fann_descale_input fann_descale_output fann_descale_train fann_destroy fann_destroy_train fann_duplicate_train_data fann_e_cant_allocate_mem fann_e_cant_open_config_r fann_e_cant_open_config_w fann_e_cant_open_td_r fann_e_cant_open_td_w fann_e_cant_read_config fann_e_cant_read_connections fann_e_cant_read_neuron fann_e_cant_read_td fann_e_cant_train_activation fann_e_cant_use_activation fann_e_cant_use_train_alg fann_e_index_out_of_bound fann_e_input_no_match fann_e_no_error fann_e_output_no_match fann_e_scale_not_present fann_e_train_data_mismatch fann_e_train_data_subset fann_e_wrong_config_version fann_e_wrong_num_connections fann_elliot fann_elliot_symmetric fann_errorfunc_linear fann_errorfunc_tanh fann_gaussian fann_gaussian_stepwise fann_gaussian_symmetric fann_get_activation_function fann_get_activation_steepness fann_get_bias_array fann_get_bit_fail fann_get_bit_fail_limit fann_get_cascade_activation_functions fann_get_cascade_activation_functions_count fann_get_cascade_activation_steepnesses fann_get_cascade_activation_steepnesses_count fann_get_cascade_candidate_change_fraction fann_get_cascade_candidate_limit fann_get_cascade_candidate_stagnation_epochs fann_get_cascade_max_cand_epochs fann_get_cascade_max_out_epochs fann_get_cascade_min_cand_epochs fann_get_cascade_min_out_epochs fann_get_cascade_num_candidate_groups fann_get_cascade_num_candidates fann_get_cascade_output_change_fraction fann_get_cascade_output_stagnation_epochs fann_get_cascade_weight_multiplier fann_get_connection_array fann_get_connection_rate fann_get_errno fann_get_errstr fann_get_layer_array fann_get_learning_momentum fann_get_learning_rate fann_get_mse fann_get_network_type fann_get_num_input fann_get_num_layers fann_get_num_output fann_get_quickprop_decay fann_get_quickprop_mu fann_get_rprop_decrease_factor fann_get_rprop_delta_max fann_get_rprop_delta_min fann_get_rprop_delta_zero fann_get_rprop_increase_factor fann_get_sarprop_step_error_shift fann_get_sarprop_step_error_threshold_factor fann_get_sarprop_temperature fann_get_sarprop_weight_decay_shift fann_get_total_connections fann_get_total_neurons fann_get_train_error_function fann_get_train_stop_function fann_get_training_algorithm fann_init_weights fann_length_train_data fann_linear fann_linear_piece fann_linear_piece_symmetric fann_merge_train_data fann_nettype_layer fann_nettype_shortcut fann_num_input_train_data fann_num_output_train_data fann_print_error fann_randomize_weights fann_read_train_from_file fann_reset_errno fann_reset_errstr fann_reset_mse fann_run fann_save fann_save_train fann_scale_input fann_scale_input_train_data fann_scale_output fann_scale_output_train_data fann_scale_train fann_scale_train_data fann_set_activation_function fann_set_activation_function_hidden fann_set_activation_function_layer fann_set_activation_function_output fann_set_activation_steepness fann_set_activation_steepness_hidden fann_set_activation_steepness_layer fann_set_activation_steepness_output fann_set_bit_fail_limit fann_set_callback fann_set_cascade_activation_functions fann_set_cascade_activation_steepnesses fann_set_cascade_candidate_change_fraction fann_set_cascade_candidate_limit fann_set_cascade_candidate_stagnation_epochs fann_set_cascade_max_cand_epochs fann_set_cascade_max_out_epochs fann_set_cascade_min_cand_epochs fann_set_cascade_min_out_epochs fann_set_cascade_num_candidate_groups fann_set_cascade_output_change_fraction fann_set_cascade_output_stagnation_epochs fann_set_cascade_weight_multiplier fann_set_error_log fann_set_input_scaling_params fann_set_learning_momentum fann_set_learning_rate fann_set_output_scaling_params fann_set_quickprop_decay fann_set_quickprop_mu fann_set_rprop_decrease_factor fann_set_rprop_delta_max fann_set_rprop_delta_min fann_set_rprop_delta_zero fann_set_rprop_increase_factor fann_set_sarprop_step_error_shift fann_set_sarprop_step_error_threshold_factor fann_set_sarprop_temperature fann_set_sarprop_weight_decay_shift fann_set_scaling_params fann_set_train_error_function fann_set_train_stop_function fann_set_training_algorithm fann_set_weight fann_set_weight_array fann_shuffle_train_data fann_sigmoid fann_sigmoid_stepwise fann_sigmoid_symmetric fann_sigmoid_symmetric_stepwise fann_sin fann_sin_symmetric fann_stopfunc_bit fann_stopfunc_mse fann_subset_train_data fann_test fann_test_data fann_threshold fann_threshold_symmetric fann_train fann_train_batch fann_train_epoch fann_train_incremental fann_train_on_data fann_train_on_file fann_train_quickprop fann_train_rprop fann_train_sarprop fastcgi_finish_request fbsql_affected_rows fbsql_assoc fbsql_autocommit fbsql_blob_size fbsql_both fbsql_change_user fbsql_clob_size fbsql_close fbsql_commit fbsql_connect fbsql_create_blob fbsql_create_clob fbsql_create_db fbsql_data_seek fbsql_database fbsql_database_password fbsql_db_query fbsql_db_status fbsql_drop_db fbsql_errno fbsql_error fbsql_fetch_array fbsql_fetch_assoc fbsql_fetch_field fbsql_fetch_lengths fbsql_fetch_object fbsql_fetch_row fbsql_field_flags fbsql_field_len fbsql_field_name fbsql_field_seek fbsql_field_table fbsql_field_type fbsql_free_result fbsql_get_autostart_info fbsql_hostname fbsql_insert_id fbsql_iso_read_committed fbsql_iso_read_uncommitted fbsql_iso_repeatable_read fbsql_iso_serializable fbsql_iso_versioned fbsql_list_dbs fbsql_list_fields fbsql_list_tables fbsql_lob_direct fbsql_lob_handle fbsql_lock_deferred fbsql_lock_optimistic fbsql_lock_pessimistic fbsql_next_result fbsql_noexec fbsql_num fbsql_num_fields fbsql_num_rows fbsql_password fbsql_pconnect fbsql_query fbsql_read_blob fbsql_read_clob fbsql_result fbsql_rollback fbsql_rows_fetched fbsql_running fbsql_select_db fbsql_set_characterset fbsql_set_lob_mode fbsql_set_password fbsql_set_transaction fbsql_start_db fbsql_starting fbsql_stop_db fbsql_stopped fbsql_stopping fbsql_table_name fbsql_tablename fbsql_unknown fbsql_username fbsql_warnings fclose fdf_add_doc_javascript fdf_add_template fdf_close fdf_create fdf_enum_values fdf_errno fdf_error fdf_get_ap fdf_get_attachment fdf_get_encoding fdf_get_file fdf_get_flags fdf_get_opt
 fdf_get_status fdf_get_value fdf_get_version fdf_header fdf_next_field_name fdf_open fdf_open_string fdf_remove_item fdf_save fdf_save_string fdf_set_ap fdf_set_encoding fdf_set_file fdf_set_flags fdf_set_javascript_action fdf_set_on_import_javascript fdf_set_opt fdf_set_status fdf_set_submit_form_action fdf_set_target_frame fdf_set_value fdf_set_version fdfaa fdfaction fdfap fdfapref fdfas fdfcalculate fdfclearff fdfclrf fdfdown fdfdownap fdfenter fdfexit fdfff fdffile fdfflags fdfformat fdfid fdfif fdfkeystroke fdfnormalap fdfrolloverap fdfsetf fdfsetff fdfstatus fdfup fdfvalidate fdfvalue feof fflush fgetc fgetcsv fgets fgetss file file_append file_binary file_exists file_get_contents file_ignore_new_lines file_no_default_context file_put_contents file_skip_empty_lines file_text file_use_include_path fileatime filectime filegroup fileinfo_continue fileinfo_devices fileinfo_mime fileinfo_mime_encoding fileinfo_mime_type fileinfo_none fileinfo_preserve_atime fileinfo_raw fileinfo_symlink fileinode filemtime fileowner fileperms filepro filepro_fieldcount filepro_fieldname filepro_fieldtype filepro_fieldwidth filepro_retrieve filepro_rowcount filesize filetype filter_callback filter_default filter_flag_allow_fraction filter_flag_allow_hex filter_flag_allow_octal filter_flag_allow_scientific filter_flag_allow_thousand filter_flag_empty_string_null filter_flag_encode_amp filter_flag_encode_high filter_flag_encode_low filter_flag_host_required filter_flag_ipv4 filter_flag_ipv6 filter_flag_no_encode_quotes filter_flag_no_priv_range filter_flag_no_res_range filter_flag_none filter_flag_path_required filter_flag_query_required filter_flag_scheme_required filter_flag_strip_backtick filter_flag_strip_high filter_flag_strip_low filter_force_array filter_has_var filter_id filter_input filter_input_array filter_list filter_null_on_failure filter_require_array filter_require_scalar filter_sanitize_email filter_sanitize_encoded filter_sanitize_full_special_chars filter_sanitize_magic_quotes filter_sanitize_number_float filter_sanitize_number_int filter_sanitize_special_chars filter_sanitize_string filter_sanitize_stripped filter_sanitize_url filter_unsafe_raw filter_validate_boolean filter_validate_email filter_validate_float filter_validate_int filter_validate_ip filter_validate_mac filter_validate_regexp filter_validate_url filter_var filter_var_array final finally finfo_buffer finfo_close finfo_file finfo_open finfo_set_flags firebird/interbase float floatval flock floor flush fmod fnm_casefold fnm_noescape fnm_pathname fnm_period fnmatch fopen for force_deflate force_gzip foreach forward_static_call forward_static_call_array fpassthru fpe_fltdiv fpe_fltinv fpe_fltovf fpe_fltres fpe_fltsub fpe_fltund fpe_intdiv fpe_intovf fprintf fputcsv fputs frac_digits fread frenchtojd fscanf fseek fsockopen fstat ft_internal ft_not ft_peek ft_prefetchtext ft_uid ftell ftok ftp_alloc ftp_ascii ftp_autoresume ftp_autoseek ftp_binary ftp_cdup ftp_chdir ftp_chmod ftp_close ftp_connect ftp_delete ftp_exec ftp_failed ftp_fget ftp_finished ftp_fput ftp_get ftp_get_option ftp_image ftp_login ftp_mdtm ftp_mkdir ftp_moredata ftp_nb_continue ftp_nb_fget ftp_nb_fput ftp_nb_get ftp_nb_put ftp_nlist ftp_pasv ftp_put ftp_pwd ftp_quit ftp_raw ftp_rawlist ftp_rename ftp_rmdir ftp_set_option ftp_site ftp_size ftp_ssl_connect ftp_systype ftp_text ftp_timeout_sec ftruncate func_get_arg func_get_args func_num_args function function_exists function_trace fwrite gc_collect_cycles gc_disable gc_enable gc_enabled gd_bundled gd_extra_version gd_info gd_major_version gc_mem_caches gd_minor_version gd_release_version gd_version geoip_asnum_by_name geoip_asnum_edition geoip_cabledsl_speed geoip_city_edition_rev0 geoip_city_edition_rev1 geoip_continent_code_by_name geoip_corporate_speed geoip_country_code3_by_name geoip_country_code_by_name geoip_country_edition geoip_country_name_by_name geoip_database_info geoip_db_avail geoip_db_filename geoip_db_get_all_info geoip_dialup_speed geoip_domain_by_name geoip_domain_edition geoip_id_by_name geoip_isp_by_name geoip_isp_edition geoip_netspeed_edition geoip_netspeedcell_by_name geoip_org_by_name geoip_org_edition geoip_proxy_edition geoip_record_by_name geoip_region_by_name geoip_region_edition_rev0 geoip_region_edition_rev1 geoip_region_name_by_code geoip_setup_custom_directory geoip_time_zone_by_country_and_region geoip_unknown_speed get_browser get_called_class get_cfg_var get_class get_class_methods get_class_vars get_current_user get_declared_classes get_declared_interfaces get_declared_traits get_defined_constants get_defined_functions get_defined_vars get_extension_funcs get_headers get_html_translation_table get_include_path get_included_files get_loaded_extensions get_magic_quotes_gpc get_magic_quotes_runtime get_meta_tags get_object_vars get_parent_class get_required_files get_resource_type get_resources getallheaders getcwd getdate getdir getenv gethostbyaddr gethostbyname gethostbynamel gethostname getimagesize getimagesizefromstring getlastmod getmxrr getmygid getmyinode getmypid getmyuid getopt getprotobyname getprotobynumber getrandmax getrusage getservbyname getservbyport gettext gettimeofday gettype glob glob_available_flags glob_brace glob_err glob_mark glob_nocheck glob_noescape glob_nosort glob_onlydir global globals gmdate gmmktime gmp_abs gmp_add gmp_and gmp_big_endian gmp_clrbit gmp_cmp gmp_com gmp_div gmp_div_q gmp_div_qr gmp_div_r gmp_divexact gmp_export gmp_fact gmp_gcd gmp_gcdext gmp_hamdist gmp_import gmp_init gmp_intval gmp_invert gmp_jacobi gmp_legendre gmp_little_endian gmp_lsw_first gmp_mod gmp_mpir_version gmp_msw_first gmp_mul gmp_native_endian gmp_neg gmp_nextprime gmp_or gmp_perfect_square gmp_popcount gmp_pow gmp_powm gmp_prob_prime gmp_random gmp_random_bits gmp_random_range gmp_random_seed gmp_root gmp_rootrem gmp_round_minusinf gmp_round_plusinf gmp_round_zero gmp_scan0 gmp_scan1 gmp_setbit gmp_sign gmp_sqrt gmp_sqrtrem gmp_strval gmp_sub gmp_testbit gmp_version gmp_xor gmstrftime gnupg_adddecryptkey gnupg_addencryptkey gnupg_addsignkey gnupg_cleardecryptkeys gnupg_clearencryptkeys gnupg_clearsignkeys gnupg_decrypt gnupg_decryptverify gnupg_encrypt gnupg_encryptsign gnupg_error_exception gnupg_error_silent gnupg_error_warning gnupg_export gnupg_geterror gnupg_getprotocol gnupg_import gnupg_init gnupg_keyinfo gnupg_protocol_cms gnupg_protocol_openpgp gnupg_setarmor gnupg_seterrormode gnupg_setsignmode gnupg_sig_mode_clear gnupg_sig_mode_detach gnupg_sig_mode_normal gnupg_sign gnupg_sigsum_bad_policy gnupg_sigsum_crl_missing gnupg_sigsum_crl_too_old gnupg_sigsum_green gnupg_sigsum_key_expired gnupg_sigsum_key_missing gnupg_sigsum_key_revoked gnupg_sigsum_red gnupg_sigsum_sig_expired gnupg_sigsum_sys_error gnupg_sigsum_valid gnupg_validity_full gnupg_validity_marginal gnupg_validity_never gnupg_validity_ultimate gnupg_validity_undefined gnupg_validity_unknown gnupg_verify gopher_binary gopher_binhex gopher_directory gopher_document gopher_dosbinary gopher_http gopher_info gopher_parsedir gopher_unknown gopher_uuencoded goto grapheme_extr_count grapheme_extr_maxbytes grapheme_extr_maxchars grapheme_extract grapheme_stripos grapheme_stristr grapheme_strlen grapheme_strpos grapheme_strripos grapheme_strrpos grapheme_strstr grapheme_substr gregoriantojd grouping gupnp_context_get_host_ip gupnp_context_get_port gupnp_context_get_subscription_timeout gupnp_context_host_path gupnp_context_new gupnp_context_set_subscription_timeout gupnp_context_timeout_add gupnp_context_unhost_path gupnp_control_error_action_failed gupnp_control_error_invalid_action gupnp_control_error_invalid_args gupnp_control_error_out_of_sync gupnp_control_point_browse_start gupnp_control_point_browse_stop gupnp_control_point_callback_set gupnp_control_point_new gupnp_device_action_callback_set gupnp_device_info_get gupnp_device_info_get_service gupnp_root_device_get_available gupnp_root_device_get_relative_location gupnp_root_device_new gupnp_root_device_set_available gupnp_root_device_start gupnp_root_device_stop gupnp_service_action_get gupnp_service_action_return gupnp_service_action_return_error gupnp_service_action_set gupnp_service_freeze_notify gupnp_service_info_get gupnp_service_info_get_introspection gupnp_service_introspection_get_state_variable gupnp_service_notify gupnp_service_proxy_action_get gupnp_service_proxy_action_set gupnp_service_proxy_add_notify gupnp_service_proxy_callback_set gupnp_service_proxy_get_subscribed gupnp_service_proxy_remove_notify gupnp_service_proxy_send_action gupnp_service_proxy_set_subscribed gupnp_service_thaw_notify gupnp_signal_action_invoked gupnp_signal_device_proxy_available gupnp_signal_device_proxy_unavailable gupnp_signal_notify_failed gupnp_signal_service_proxy_available gupnp_signal_service_proxy_unavailable gupnp_signal_subscription_lost gupnp_type_boolean gupnp_type_double gupnp_type_float gupnp_type_int gupnp_type_long gupnp_type_string gzclose gzcompress gzdecode gzdeflate gzencode gzeof gzfile gzgetc gzgets gzgetss gzinflate gzopen gzpassthru gzputs gzread gzrewind gzseek gztell gzuncompress gzwrite hash hash_algos hash_copy hash_equals hash_file hash_final hash_hmac hash_hmac_file hash_init hash_pbkdf2 hash_update hash_update_file hash_update_stream header header_register_callback header_remove headers_list headers_sent hebrev hebrevc hex2bin hexdec highlight_file highlight_string html_entities html_entity_decode html_specialchars htmlentities htmlspecialchars htmlspecialchars_decode http_auth_any http_auth_basic http_auth_digest http_auth_gssneg http_auth_ntlm http_build_cookie http_build_query http_build_str http_build_url http_cache_etag http_cache_last_modified http_chunked_decode http_cookie_httponly http_cookie_parse_raw http_cookie_secure http_date http_deflate http_deflate_level_def
 http_deflate_level_max http_deflate_level_min http_deflate_strategy_def http_deflate_strategy_filt http_deflate_strategy_fixed http_deflate_strategy_huff http_deflate_strategy_rle http_deflate_type_gzip http_deflate_type_raw http_deflate_type_zlib http_e_encoding http_e_header http_e_invalid_param http_e_malformed_headers http_e_message_type http_e_querystring http_e_request http_e_request_method http_e_request_pool http_e_response http_e_runtime http_e_socket http_e_url http_encoding_stream_flush_full http_encoding_stream_flush_none http_encoding_stream_flush_sync http_get http_get_request_body http_get_request_body_stream http_get_request_headers http_head http_inflate http_ipresolve_any http_ipresolve_v4 http_ipresolve_v6 http_match_etag http_match_modified http_match_request_header http_meth_acl http_meth_baseline_control http_meth_checkin http_meth_checkout http_meth_connect http_meth_copy http_meth_delete http_meth_get http_meth_head http_meth_label http_meth_lock http_meth_merge http_meth_mkactivity http_meth_mkcol http_meth_mkworkspace http_meth_move http_meth_options http_meth_post http_meth_propfind http_meth_proppatch http_meth_put http_meth_report http_meth_trace http_meth_uncheckout http_meth_unlock http_meth_update http_meth_version_control http_msg_none http_msg_request http_msg_response http_negotiate_charset http_negotiate_content_type http_negotiate_language http_params_allow_comma http_params_allow_failure http_params_default http_params_raise_error http_parse_cookie http_parse_headers http_parse_message http_parse_params http_persistent_handles_clean http_persistent_handles_count http_persistent_handles_ident http_post_data http_post_fields http_proxy_http http_proxy_socks4 http_proxy_socks5 http_put_data http_put_file http_put_stream http_querystring_type_array http_querystring_type_bool http_querystring_type_float http_querystring_type_int http_querystring_type_object http_querystring_type_string http_redirect http_redirect_found http_redirect_perm http_redirect_post http_redirect_proxy http_redirect_temp http_request http_request_body_encode http_request_method_exists http_request_method_name http_request_method_register http_request_method_unregister http_response_code http_send_content_disposition http_send_content_type http_send_data http_send_file http_send_last_modified http_send_status http_send_stream http_ssl_version_any http_ssl_version_sslv2 http_ssl_version_sslv3 http_ssl_version_tlsv1 http_support http_support_encodings http_support_magicmime http_support_requests http_support_sslrequests http_throttle http_url_join_path http_url_join_query http_url_replace http_url_strip_all http_url_strip_auth http_url_strip_fragment http_url_strip_pass http_url_strip_path http_url_strip_port http_url_strip_query http_url_strip_user http_version_1_0 http_version_1_1 http_version_any hypot ibase_add_user ibase_affected_rows ibase_backup ibase_bkp_convert ibase_bkp_ignore_checksums ibase_bkp_ignore_limbo ibase_bkp_metadata_only ibase_bkp_no_garbage_collect ibase_bkp_non_transportable ibase_bkp_old_descriptions ibase_blob_add ibase_blob_cancel ibase_blob_close ibase_blob_create ibase_blob_echo ibase_blob_get ibase_blob_import ibase_blob_info ibase_blob_open ibase_close ibase_commit ibase_commit_ret ibase_committed ibase_concurrency ibase_connect ibase_consistency ibase_db_info ibase_default ibase_delete_user ibase_drop_db ibase_errcode ibase_errmsg ibase_execute ibase_fetch_arrays ibase_fetch_assoc ibase_fetch_blobs ibase_fetch_object ibase_fetch_row ibase_field_info ibase_free_event_handler ibase_free_query ibase_free_result ibase_gen_id ibase_maintain_db ibase_modify_user ibase_name_result ibase_nowait ibase_num_fields ibase_num_params ibase_param_info ibase_pconnect ibase_prepare ibase_prp_access_mode ibase_prp_activate ibase_prp_am_readonly ibase_prp_am_readwrite ibase_prp_db_online ibase_prp_deny_new_attachments ibase_prp_deny_new_transactions ibase_prp_page_buffers ibase_prp_res ibase_prp_res_use_full ibase_prp_reserve_space ibase_prp_set_sql_dialect ibase_prp_shutdown_db ibase_prp_sweep_interval ibase_prp_wm_async ibase_prp_wm_sync ibase_prp_write_mode ibase_query ibase_read ibase_res_create ibase_res_deactivate_idx ibase_res_no_shadow ibase_res_no_validity ibase_res_one_at_a_time ibase_res_replace ibase_res_use_all_space ibase_restore ibase_rollback ibase_rollback_ret ibase_rpr_check_db ibase_rpr_full ibase_rpr_ignore_checksum ibase_rpr_kill_shadows ibase_rpr_mend_db ibase_rpr_sweep_db ibase_rpr_validate_db ibase_server_info ibase_service_attach ibase_service_detach ibase_set_event_handler ibase_sts_data_pages ibase_sts_db_log ibase_sts_hdr_pages ibase_sts_idx_pages ibase_sts_sys_relations ibase_svc_get_env ibase_svc_get_env_lock ibase_svc_get_env_msg ibase_svc_get_users ibase_svc_implementation ibase_svc_server_version ibase_svc_svr_db_info ibase_svc_user_dbpath ibase_trans ibase_unixtime ibase_wait ibase_wait_event ibase_write iconv iconv_get_encoding iconv_impl iconv_mime_decode iconv_mime_decode_continue_on_error iconv_mime_decode_headers iconv_mime_decode_strict iconv_mime_encode iconv_set_encoding iconv_strlen iconv_strpos iconv_strrpos iconv_substr iconv_version id3_best id3_get_frame_long_name id3_get_frame_short_name id3_get_genre_id id3_get_genre_list id3_get_genre_name id3_get_tag id3_get_version id3_remove_tag id3_set_tag id3_v1_0 id3_v1_1 id3_v2_1 id3_v2_2 id3_v2_3 id3_v2_4 idate idn_to_ascii idn_to_unicode idn_to_utf8 idna_allow_unassigned idna_check_bidi idna_check_contextj idna_default idna_error_bidi idna_error_contextj idna_error_disallowed idna_error_domain_name_too_long idna_error_empty_label idna_error_hyphen_3_4 idna_error_invalid_ace_label idna_error_label_has_dot idna_error_label_too_long idna_error_leading_combining_mark idna_error_leading_hyphen idna_error_punycode idna_error_trailing_hyphen idna_nontransitional_to_ascii idna_nontransitional_to_unicode idna_use_std3_rules if ifx_affected_rows ifx_blobinfile_mode ifx_byteasvarchar ifx_close ifx_connect ifx_copy_blob ifx_create_blob ifx_create_char ifx_do ifx_error ifx_errormsg ifx_fetch_row ifx_fieldproperties ifx_fieldtypes ifx_free_blob ifx_free_char ifx_free_result ifx_get_blob ifx_get_char ifx_getsqlca ifx_hold ifx_htmltbl_result ifx_lo_append ifx_lo_buffer ifx_lo_nobuffer ifx_lo_rdonly ifx_lo_rdwr ifx_lo_wronly ifx_nullformat ifx_num_fields ifx_num_rows ifx_pconnect ifx_prepare ifx_query ifx_scroll ifx_textasvarchar ifx_update_blob ifx_update_char ifxus_close_slob ifxus_create_slob ifxus_free_slob ifxus_open_slob ifxus_read_slob ifxus_seek_slob ifxus_tell_slob ifxus_write_slob ignore_user_abort iis_add_server iis_anonymous iis_basic iis_execute iis_get_dir_security iis_get_script_map iis_get_server_by_comment iis_get_server_by_path iis_get_server_rights iis_get_service_state iis_ntlm iis_paused iis_read iis_remove_server iis_running iis_script iis_set_app_settings iis_set_dir_security iis_set_script_map iis_set_server_rights iis_start_server iis_start_service iis_starting iis_stop_server iis_stop_service iis_stopped iis_write ill_badstk ill_coproc ill_illadr ill_illopc ill_illopn ill_illtrp ill_prvopc ill_prvreg image2wbmp image_type_to_extension image_type_to_mime_type imageaffine imageaffinematrixconcat imageaffinematrixget imagealphablending imageantialias imagearc imagechar imagecharup imagecolorallocate imagecolorallocatealpha imagecolorat imagecolorclosest imagecolorclosestalpha imagecolorclosesthwb imagecolordeallocate imagecolorexact imagecolorexactalpha imagecolormatch imagecolorresolve imagecolorresolvealpha imagecolorset imagecolorsforindex imagecolorstotal imagecolortransparent imageconvolution imagecopy imagecopymerge imagecopymergegray imagecopyresampled imagecopyresized imagecreate imagecreatefromgd imagecreatefromgd2 imagecreatefromgd2part imagecreatefromgif imagecreatefromjpeg imagecreatefrompng imagecreatefromstring imagecreatefromwbmp imagecreatefromwebp imagecreatefromxbm imagecreatefromxpm imagecreatetruecolor imagecrop imagecropauto imagedashedline imagedestroy imageellipse imagefill imagefilledarc imagefilledellipse imagefilledpolygon imagefilledrectangle imagefilltoborder imagefilter imageflip imagefontheight imagefontwidth imageftbbox imagefttext imagegammacorrect imagegd imagegd2 imagegif imagegrabscreen imagegrabwindow imageinterlace imageistruecolor imagejpeg imagelayereffect imageline imageloadfont imagepalettecopy imagepalettetotruecolor imagepng imagepolygon imagepsbbox imagepsencodefont imagepsextendfont imagepsfreefont imagepsloadfont imagepsslantfont imagepstext imagerectangle imagerotate imagesavealpha imagescale imagesetbrush imagesetinterpolation imagesetpixel imagesetstyle imagesetthickness imagesettile imagestring imagestringup imagesx imagesy imagetruecolortopalette imagettfbbox imagettftext imagetype_bmp imagetype_count imagetype_gif imagetype_ico imagetype_iff imagetype_jb2 imagetype_jp2 imagetype_jpc imagetype_jpeg imagetype_jpeg2000 imagetype_jpx imagetype_png imagetype_psd imagetype_swc imagetype_swf imagetype_tiff_ii imagetype_tiff_mm imagetype_unknown imagetype_wbmp imagetype_xbm imagetypes imagewbmp imagewebp imagexbm imap_8bit imap_alerts imap_append imap_base64 imap_binary imap_body imap_bodystruct imap_check imap_clearflag_full imap_close imap_closetimeout imap_create imap_createmailbox imap_delete imap_deletemailbox imap_errors imap_expunge imap_fetch_overview imap_fetchbody imap_fetchheader imap_fetchmime imap_fetchstructure imap_fetchtext imap_gc imap_gc_elt imap_gc_env imap_gc_texts imap_get_quota imap_get_quotaroot imap_getacl imap_getmailboxes imap_getsubscribed imap_header imap_headerinfo imap_headers imap_last_error imap_list imap_listmailbox imap_listscan imap_listsubscribed imap_lsub imap_mail imap_mail_compose imap_mail_copy imap_mail_move
 imap_mailboxmsginfo imap_mime_header_decode imap_msgno imap_mutf7_to_utf8 imap_num_msg imap_num_recent imap_open imap_opentimeout imap_ping imap_qprint imap_readtimeout imap_rename imap_renamemailbox imap_reopen imap_rfc822_parse_adrlist imap_rfc822_parse_headers imap_rfc822_write_address imap_savebody imap_scan imap_scanmailbox imap_search imap_set_quota imap_setacl imap_setflag_full imap_sort imap_status imap_subscribe imap_thread imap_timeout imap_uid imap_undelete imap_unsubscribe imap_utf7_decode imap_utf7_encode imap_utf8 imap_utf8_to_mutf7 imap_writetimeout img_affine_rotate img_affine_scale img_affine_shear_horizontal img_affine_shear_vertical img_affine_translate img_arc_chord img_arc_edged img_arc_nofill img_arc_pie img_arc_rounded img_bell img_bessel img_bicubic img_bicubic_fixed img_bilinear_fixed img_blackman img_box img_bspline img_catmullrom img_color_brushed img_color_styled img_color_styledbrushed img_color_tiled img_color_transparent img_crop_black img_crop_default img_crop_sides img_crop_threshold img_crop_transparent img_crop_white img_effect_alphablend img_effect_normal img_effect_overlay img_effect_replace img_filter_brightness img_filter_colorize img_filter_contrast img_filter_edgedetect img_filter_emboss img_filter_gaussian_blur img_filter_grayscale img_filter_mean_removal img_filter_negate img_filter_pixelate img_filter_selective_blur img_filter_smooth img_flip_both img_flip_horizontal img_flip_vertical img_gaussian img_gd2_compressed img_gd2_raw img_generalized_cubic img_gif img_hamming img_hanning img_hermite img_jpeg img_jpg img_mitchell img_nearest_neighbour img_png img_power img_quadratic img_sinc img_triangle img_wbmp img_weighted4 img_xpm implements implode import_request_variables in_access in_all_events in_array in_attrib in_close in_close_nowrite in_close_write in_create in_delete in_delete_self in_dont_follow in_ignored in_isdir in_mask_add in_modify in_move in_move_self in_moved_from in_moved_to in_oneshot in_onlydir in_open in_q_overflow in_unmount include include_once inet_ntop inet_pton inf info_all info_configuration info_credits info_environment info_general info_license info_modules info_variables ingres_api_version ingres_assoc ingres_autocommit ingres_autocommit_state ingres_both ingres_charset ingres_close ingres_commit ingres_connect ingres_cursor ingres_cursor_readonly ingres_cursor_update ingres_date_dmy ingres_date_finnish ingres_date_german ingres_date_iso ingres_date_iso4 ingres_date_mdy ingres_date_multinational ingres_date_multinational4 ingres_date_ymd ingres_errno ingres_error ingres_errsqlstate ingres_escape_string ingres_execute ingres_ext_version ingres_fetch_array ingres_fetch_assoc ingres_fetch_object ingres_fetch_proc_return ingres_fetch_row ingres_field_length ingres_field_name ingres_field_nullable ingres_field_precision ingres_field_scale ingres_field_type ingres_free_result ingres_money_leading ingres_money_trailing ingres_next_error ingres_num ingres_num_fields ingres_num_rows ingres_pconnect ingres_prepare ingres_query ingres_result_seek ingres_rollback ingres_set_environment ingres_structure_btree ingres_structure_cbtree ingres_structure_chash ingres_structure_cheap ingres_structure_cisam ingres_structure_hash ingres_structure_heap ingres_structure_isam ingres_unbuffered_query ini_all ini_alter ini_get ini_get_all ini_perdir ini_restore ini_scanner_normal ini_scanner_raw ini_scanner_typed ini_set ini_system ini_user inotify_add_watch inotify_init inotify_queue_len inotify_read inotify_rm_watch input_cookie input_env input_get input_post input_request input_server input_session instanceof insteadof int int_curr_symbol int_frac_digits intdiv integer interface interface_exists intl_error_name intl_get_error_code intl_get_error_message intl_icu_data_version intl_icu_version intl_idna_variant_2003 intl_idna_variant_uts46 intl_is_failure intl_max_locale_len intval ion_clock_skew ion_corrupt_file ion_expired_file ion_license_corrupt ion_license_expired ion_license_header_invalid ion_license_not_found ion_license_property_invalid ion_license_server_invalid ion_no_permissions ion_unauth_append_prepend_file ion_unauth_included_file ion_unauth_including_file ion_untrusted_extension ioncube_check_license_properties ioncube_file_info ioncube_file_is_encoded ioncube_file_not_permissioned ioncube_file_properties ioncube_license_has_expired ioncube_license_matches_server ioncube_license_properties ioncube_licensed_servers ioncube_loader_iversion ioncube_loader_version ioncube_read_file ioncube_server_data ioncube_write_file ip2long ip_multicast_if ip_multicast_loop ip_multicast_ttl ipproto_ip ipproto_ipv6 iptcembed iptcparse ipv6_hoplimit ipv6_multicast_hops ipv6_multicast_if ipv6_multicast_loop ipv6_pktinfo ipv6_recvhoplimit ipv6_recvpktinfo ipv6_recvtclass ipv6_tclass ipv6_unicast_hops is_a is_array is_bool is_callable is_dir is_double is_executable is_file is_finite is_float is_infinite is_int is_integer is_link is_long is_nan is_null is_numeric is_object is_readable is_real is_resource is_scalar is_soap_fault is_string is_subclass_of is_tainted is_uploaded_file is_writable is_writeable isset iterator_apply iterator_count iterator_to_array jddayofweek jdmonthname jdtofrench jdtogregorian jdtojewish jdtojulian jdtounix jewishtojd join jpeg2wbmp json_bigint_as_string json_decode json_encode json_error_ctrl_char json_error_depth json_error_inf_or_nan json_error_none json_error_recursion json_error_state_mismatch json_error_syntax json_error_unsupported_type json_error_utf8 json_force_object json_hex_amp json_hex_apos json_hex_quot json_hex_tag json_last_error json_last_error_msg json_numeric_check json_object_as_array json_partial_output_on_error json_preserve_zero_fraction json_pretty_print json_unescaped_slashes json_unescaped_unicode judy_type judy_version juliantojd kadm5_attributes kadm5_chpass_principal kadm5_clearpolicy kadm5_create_principal kadm5_delete_principal kadm5_destroy kadm5_fail_auth_count kadm5_flush kadm5_get_policies kadm5_get_principal kadm5_get_principals kadm5_init_with_password kadm5_kvno kadm5_last_failed kadm5_last_pw_change kadm5_last_success kadm5_max_life kadm5_max_rlife kadm5_mod_name kadm5_mod_time kadm5_modify_principal kadm5_policy kadm5_princ_expire_time kadm5_principal kadm5_pw_expiration kadm5_randkey key key_exists krb5_kdb_disallow_all_tix krb5_kdb_disallow_dup_skey krb5_kdb_disallow_forwardable krb5_kdb_disallow_postdated krb5_kdb_disallow_proxiable krb5_kdb_disallow_renewable krb5_kdb_disallow_svr krb5_kdb_disallow_tgt_based krb5_kdb_new_princ krb5_kdb_pwchange_server krb5_kdb_requires_hw_auth krb5_kdb_requires_pre_auth krb5_kdb_requires_pwchange krb5_kdb_support_desmd5 krsort ksort latt_haschildren latt_hasnochildren latt_marked latt_noinferiors latt_noselect latt_referral latt_unmarked lc_all lc_collate lc_ctype lc_messages lc_monetary lc_numeric lc_time lcfirst lcg_value lchgrp lchown ldap_8859_to_t61 ldap_add ldap_bind ldap_close ldap_compare ldap_connect ldap_control_paged_result ldap_control_paged_result_response ldap_count_entries ldap_delete ldap_dn2ufn ldap_err2str ldap_errno ldap_error ldap_escape ldap_explode_dn ldap_first_attribute ldap_first_entry ldap_first_reference ldap_free_result ldap_get_attributes ldap_get_dn ldap_get_entries ldap_get_option ldap_get_values ldap_get_values_len ldap_list ldap_mod_add ldap_mod_del ldap_mod_replace ldap_modify ldap_modify_batch ldap_next_attribute ldap_next_entry ldap_next_reference ldap_parse_reference ldap_parse_result ldap_read ldap_rename ldap_sasl_bind ldap_search ldap_set_option ldap_set_rebind_proc ldap_sort ldap_start_tls ldap_t61_to_8859 ldap_unbind levenshtein libexslt_dotted_version libexslt_version libxml_clear_errors libxml_compact libxml_disable_entity_loader libxml_dotted_version libxml_dtdattr libxml_dtdload libxml_dtdvalid libxml_err_error libxml_err_fatal libxml_err_none libxml_err_warning libxml_get_errors libxml_get_last_error libxml_html_nodefdtd libxml_html_noimplied libxml_loaded_version libxml_noblanks libxml_nocdata libxml_noemptytag libxml_noent libxml_noerror libxml_nonet libxml_nowarning libxml_noxmldecl libxml_nsclean libxml_parsehuge libxml_pedantic libxml_schema_create libxml_set_external_entity_loader libxml_set_streams_context libxml_use_internal_errors libxml_version libxml_xinclude libxslt_dotted_version libxslt_version link linkinfo list locale_accept_from_http locale_canonicalize locale_compose locale_filter_matches locale_get_all_variants locale_get_default locale_get_display_language locale_get_display_name locale_get_display_region locale_get_display_script locale_get_display_variant locale_get_keywords locale_get_primary_language locale_get_region locale_get_script locale_lookup locale_parse locale_set_default localeconv localtime lock_ex lock_nb lock_sh lock_un log log10 log1p log_alert log_auth log_authpriv log_cons log_crit log_cron log_daemon log_debug log_emerg log_err log_info log_kern log_local0 log_local1 log_local2 log_local3 log_local4 log_local5 log_local6 log_local7 log_lpr log_mail log_ndelay log_news log_notice log_nowait log_odelay log_perror log_pid log_syslog log_user log_uucp log_warning long2ip lstat ltrim lzf_compress lzf_decompress lzf_optimized_for m_1_pi m_2_pi m_2_sqrtpi m_checkstatus m_completeauthorizations m_connect m_connectionerror m_deletetrans m_destroyconn m_destroyengine m_done m_e m_error m_euler m_fail m_getcell m_getcellbynum m_getcommadelimited m_getheader m_initconn m_initengine m_iscommadelimited m_ln10 m_ln2 m_lnpi m_log10e m_log2e m_maxconntimeout m_monitor m_numcolumns m_numrows m_parsecommadelimited m_pending m_pi m_pi_2 m_pi_4 m_responsekeys m_responseparam m_returnstatus m_setblocking m_setdropfile m_setip m_setssl m_setssl_cafile m_setssl_files m_settimeout m_sqrt1_2 m_sqrt2
 m_sqrt3 m_sqrtpi m_sslcert_gen_hash m_success m_transactionssent m_transinqueue m_transkeyval m_transnew m_transsend m_uwait m_validateidentifier m_verifyconnection m_verifysslcert magic_quotes_runtime mail mailparse_determine_best_xfer_encoding mailparse_extract_output mailparse_extract_return mailparse_extract_stream mailparse_msg_create mailparse_msg_extract_part mailparse_msg_extract_part_file mailparse_msg_extract_whole_part_file mailparse_msg_free mailparse_msg_get_part mailparse_msg_get_part_data mailparse_msg_get_structure mailparse_msg_parse mailparse_msg_parse_file mailparse_rfc822_parse_addresses mailparse_stream_encode mailparse_uudecode_all main max maxdb_affected_rows maxdb_application maxdb_appversion maxdb_assoc maxdb_assoc_lower maxdb_assoc_upper maxdb_autocommit maxdb_bind_param maxdb_bind_result maxdb_both maxdb_change_user maxdb_character_set_name maxdb_client_encoding maxdb_close maxdb_close_long_data maxdb_commit maxdb_compname maxdb_connect maxdb_connect_errno maxdb_connect_error maxdb_cursorprefix maxdb_data_seek maxdb_debug maxdb_disable_reads_from_master maxdb_disable_rpl_parse maxdb_dump_debug_info maxdb_embedded_connect maxdb_enable_reads_from_master maxdb_enable_rpl_parse maxdb_errno maxdb_error maxdb_escape_string maxdb_execute maxdb_fetch maxdb_fetch_array maxdb_fetch_assoc maxdb_fetch_field maxdb_fetch_field_direct maxdb_fetch_fields maxdb_fetch_lengths maxdb_fetch_object maxdb_fetch_row maxdb_field_count maxdb_field_seek maxdb_field_tell maxdb_free_result maxdb_get_client_info maxdb_get_client_version maxdb_get_host_info maxdb_get_metadata maxdb_get_proto_info maxdb_get_server_info maxdb_get_server_version maxdb_info maxdb_init maxdb_insert_id maxdb_isolationlevel maxdb_kill maxdb_master_query maxdb_more_results maxdb_multi_query maxdb_next_result maxdb_num maxdb_num_fields maxdb_num_rows maxdb_options maxdb_packetcount maxdb_param_count maxdb_ping maxdb_prepare maxdb_query maxdb_real_connect maxdb_real_escape_string maxdb_real_query maxdb_report maxdb_rollback maxdb_rpl_parse_enabled maxdb_rpl_probe maxdb_rpl_query_type maxdb_select_db maxdb_send_long_data maxdb_send_query maxdb_server_end maxdb_server_init maxdb_set_opt maxdb_sqlmode maxdb_sqlstate maxdb_ssl_set maxdb_stat maxdb_statementcachesize maxdb_stmt_affected_rows maxdb_stmt_bind_param maxdb_stmt_bind_result maxdb_stmt_close maxdb_stmt_close_long_data maxdb_stmt_data_seek maxdb_stmt_errno maxdb_stmt_error maxdb_stmt_execute maxdb_stmt_fetch maxdb_stmt_free_result maxdb_stmt_init maxdb_stmt_num_rows maxdb_stmt_param_count maxdb_stmt_prepare maxdb_stmt_reset maxdb_stmt_result_metadata maxdb_stmt_send_long_data maxdb_stmt_sqlstate maxdb_stmt_store_result maxdb_store_result maxdb_thread_id maxdb_thread_safe maxdb_timeout maxdb_unicode maxdb_use_result maxdb_warning_count mb_case_lower mb_case_title mb_case_upper mb_check_encoding mb_convert_case mb_convert_encoding mb_convert_kana mb_convert_variables mb_decode_mimeheader mb_decode_numericentity mb_detect_encoding mb_detect_order mb_encode_mimeheader mb_encode_numericentity mb_encoding_aliases mb_ereg mb_ereg_match mb_ereg_replace mb_ereg_replace_callback mb_ereg_search mb_ereg_search_getpos mb_ereg_search_getregs mb_ereg_search_init mb_ereg_search_pos mb_ereg_search_regs mb_ereg_search_setpos mb_eregi mb_eregi_replace mb_get_info mb_http_input mb_http_output mb_internal_encoding mb_language mb_list_encodings mb_output_handler mb_overload_mail mb_overload_regex mb_overload_string mb_parse_str mb_preferred_mime_name mb_regex_encoding mb_regex_set_options mb_send_mail mb_split mb_strcut mb_strimwidth mb_stripos mb_stristr mb_strlen mb_strpos mb_strrchr mb_strrichr mb_strripos mb_strrpos mb_strstr mb_strtolower mb_strtoupper mb_strwidth mb_substitute_character mb_substr mb_substr_count mbereg mbereg_match mbereg_replace mbereg_search mbereg_search_getpos mbereg_search_getregs mbereg_search_init mbereg_search_pos mbereg_search_regs mbereg_search_setpos mberegi mberegi_replace mbregex_encoding mbsplit mcast_block_source mcast_join_group mcast_join_source_group mcast_leave_group mcast_leave_source_group mcast_unblock_source mcrypt_3des mcrypt_arcfour mcrypt_arcfour_iv mcrypt_blowfish mcrypt_blowfish_compat mcrypt_cast_128 mcrypt_cast_256 mcrypt_cbc mcrypt_cfb mcrypt_create_iv mcrypt_crypt mcrypt_decrypt mcrypt_des mcrypt_dev_random mcrypt_dev_urandom mcrypt_ecb mcrypt_enc_get_algorithms_name mcrypt_enc_get_block_size mcrypt_enc_get_iv_size mcrypt_enc_get_key_size mcrypt_enc_get_modes_name mcrypt_enc_get_supported_key_sizes mcrypt_enc_is_block_algorithm mcrypt_enc_is_block_algorithm_mode mcrypt_enc_is_block_mode mcrypt_enc_self_test mcrypt_encrypt mcrypt_enigna mcrypt_generic mcrypt_generic_deinit mcrypt_generic_end mcrypt_generic_init mcrypt_get_block_size mcrypt_get_cipher_name mcrypt_get_iv_size mcrypt_get_key_size mcrypt_gost mcrypt_idea mcrypt_list_algorithms mcrypt_list_modes mcrypt_loki97 mcrypt_mars mcrypt_mode_cbc mcrypt_mode_cfb mcrypt_mode_ecb mcrypt_mode_nofb mcrypt_mode_ofb mcrypt_mode_stream mcrypt_module_close mcrypt_module_get_algo_block_size mcrypt_module_get_algo_key_size mcrypt_module_get_supported_key_sizes mcrypt_module_is_block_algorithm mcrypt_module_is_block_algorithm_mode mcrypt_module_is_block_mode mcrypt_module_open mcrypt_module_self_test mcrypt_ofb mcrypt_panama mcrypt_rand mcrypt_rc2 mcrypt_rc6 mcrypt_rijndael_128 mcrypt_rijndael_192 mcrypt_rijndael_256 mcrypt_safer128 mcrypt_safer64 mcrypt_saferplus mcrypt_serpent mcrypt_skipjack mcrypt_threeway mcrypt_tripledes mcrypt_twofish mcrypt_wake mcrypt_xtea md5 md5_file mdecrypt_generic memcache_add memcache_add_server memcache_append memcache_cas memcache_close memcache_compressed memcache_connect memcache_debug memcache_decrement memcache_delete memcache_flush memcache_get memcache_get_extended_stats memcache_get_server_status memcache_get_stats memcache_get_version memcache_have_session memcache_increment memcache_pconnect memcache_prepend memcache_replace memcache_set memcache_set_compress_threshold memcache_set_failure_callback memcache_set_server_params memory_get_peak_usage memory_get_usage memory_trace metaphone method_exists mhash mhash_adler32 mhash_count mhash_crc32 mhash_crc32b mhash_fnv132 mhash_fnv164 mhash_fnv1a32 mhash_fnv1a64 mhash_get_block_size mhash_get_hash_name mhash_gost mhash_haval128 mhash_haval160 mhash_haval192 mhash_haval224 mhash_haval256 mhash_joaat mhash_keygen_s2k mhash_md2 mhash_md4 mhash_md5 mhash_ripemd128 mhash_ripemd160 mhash_ripemd256 mhash_ripemd320 mhash_sha1 mhash_sha224 mhash_sha256 mhash_sha384 mhash_sha512 mhash_snefru256 mhash_tiger mhash_tiger128 mhash_tiger160 mhash_whirlpool microtime mime_content_type min ming_keypress ming_new ming_setcubicthreshold ming_setscale ming_setswfcompression ming_useconstants ming_useswfversion ming_zlib mk_e_unavailable mkdir mktime mon_1 mon_10 mon_11 mon_12 mon_2 mon_3 mon_4 mon_5 mon_6 mon_7 mon_8 mon_9 mon_decimal_point mon_grouping mon_thousands_sep money_format mongo_stream_notify_io_completed mongo_stream_notify_io_progress mongo_stream_notify_io_read mongo_stream_notify_io_write mongo_stream_notify_log_batchinsert mongo_stream_notify_log_cmd_delete mongo_stream_notify_log_cmd_insert mongo_stream_notify_log_cmd_update mongo_stream_notify_log_delete mongo_stream_notify_log_getmore mongo_stream_notify_log_insert mongo_stream_notify_log_killcursor mongo_stream_notify_log_query mongo_stream_notify_log_response_header mongo_stream_notify_log_update mongo_stream_notify_log_write_batch mongo_stream_notify_log_write_reply mongo_stream_notify_type_io_init mongo_stream_notify_type_log mongo_streams mongo_supports_auth_mechanism_gssapi mongo_supports_auth_mechanism_mongodb_cr mongo_supports_auth_mechanism_mongodb_x509 mongo_supports_auth_mechanism_plain mongo_supports_ssl mongo_supports_streams move_uploaded_file mqseries_back mqseries_begin mqseries_close mqseries_cmit mqseries_conn mqseries_connx mqseries_disc mqseries_get mqseries_inq mqseries_mqcc_failed mqseries_mqcc_ok mqseries_mqcc_unknown mqseries_mqcc_warning mqseries_open mqseries_put mqseries_put1 mqseries_set mqseries_strerror msession_connect msession_count msession_create msession_destroy msession_disconnect msession_find msession_get msession_get_array msession_get_data msession_inc msession_list msession_listvar msession_lock msession_plugin msession_randstr msession_set msession_set_array msession_set_data msession_timeout msession_uniq msession_unlock msg_ctrunc msg_dontroute msg_dontwait msg_eagain msg_enomsg msg_eof msg_eor msg_except msg_get_queue msg_ipc_nowait msg_noerror msg_oob msg_peek msg_queue_exists msg_receive msg_remove_queue msg_send msg_set_queue msg_stat_queue msg_trunc msg_waitall msgfmt_create msgfmt_format msgfmt_format_message msgfmt_get_error_code msgfmt_get_error_message msgfmt_get_locale msgfmt_get_pattern msgfmt_parse msgfmt_parse_message msgfmt_set_pattern msql msql_affected_rows msql_assoc msql_both msql_close msql_connect msql_create_db msql_createdb msql_data_seek msql_db_query msql_dbname msql_drop_db msql_error msql_fetch_array msql_fetch_field msql_fetch_object msql_fetch_row msql_field_flags msql_field_len msql_field_name msql_field_seek msql_field_table msql_field_type msql_fieldflags msql_fieldlen msql_fieldname msql_fieldtable msql_fieldtype msql_free_result msql_list_dbs msql_list_fields msql_list_tables msql_num msql_num_fields msql_num_rows msql_numfields msql_numrows msql_pconnect msql_query msql_regcase msql_result msql_select_db msql_tablename mssql_assoc mssql_bind mssql_both mssql_close mssql_connect mssql_data_seek mssql_execute mssql_fetch_array mssql_fetch_assoc mssql_fetch_batch mssql_fetch_field mssql_fetch_object mssql_fetch_row mssql_field_length mssql_field_name mssql_field_seek mssql_field_type mssql_free_result
 mssql_free_statement mssql_get_last_message mssql_guid_string mssql_init mssql_min_error_severity mssql_min_message_severity mssql_next_result mssql_num mssql_num_fields mssql_num_rows mssql_pconnect mssql_query mssql_result mssql_rows_affected mssql_select_db mt_getrandmax mt_rand mt_srand mysql mysql_affected_rows mysql_assoc mysql_both mysql_client_compress mysql_client_encoding mysql_client_ignore_space mysql_client_interactive mysql_client_ssl mysql_close mysql_connect mysql_create_db mysql_data_seek mysql_db_name mysql_db_query mysql_dbname mysql_drop_db mysql_errno mysql_error mysql_escape_string mysql_fetch_array mysql_fetch_assoc mysql_fetch_field mysql_fetch_lengths mysql_fetch_object mysql_fetch_row mysql_field_flags mysql_field_len mysql_field_name mysql_field_seek mysql_field_table mysql_field_type mysql_fieldflags mysql_fieldlen mysql_fieldname mysql_fieldtable mysql_fieldtype mysql_free_result mysql_freeresult mysql_get_client_info mysql_get_host_info mysql_get_proto_info mysql_get_server_info mysql_info mysql_insert_id mysql_list_dbs mysql_list_fields mysql_list_processes mysql_list_tables mysql_listdbs mysql_listfields mysql_listtables mysql_num mysql_num_fields mysql_num_rows mysql_numfields mysql_numrows mysql_pconnect mysql_ping mysql_query mysql_real_escape_string mysql_result mysql_select_db mysql_selectdb mysql_set_charset mysql_stat mysql_table_name mysql_tablename mysql_thread_id mysql_unbuffered_query mysqli_affected_rows mysqli_assoc mysqli_async mysqli_auto_increment_flag mysqli_autocommit mysqli_begin_transaction mysqli_binary_flag mysqli_bind_param mysqli_bind_result mysqli_blob_flag mysqli_both mysqli_change_user mysqli_character_set_name mysqli_client_can_handle_expired_passwords mysqli_client_compress mysqli_client_encoding mysqli_client_found_rows mysqli_client_ignore_space mysqli_client_interactive mysqli_client_multi_queries mysqli_client_no_schema mysqli_client_ssl mysqli_close mysqli_commit mysqli_connect mysqli_connect_errno mysqli_connect_error mysqli_cursor_type_for_update mysqli_cursor_type_no_cursor mysqli_cursor_type_read_only mysqli_cursor_type_scrollable mysqli_data_seek mysqli_data_truncated mysqli_debug mysqli_debug_trace_enabled mysqli_dump_debug_info mysqli_embedded_server_end mysqli_embedded_server_start mysqli_enum_flag mysqli_errno mysqli_error mysqli_error_list mysqli_escape_string mysqli_execute mysqli_fetch mysqli_fetch_all mysqli_fetch_array mysqli_fetch_assoc mysqli_fetch_field mysqli_fetch_field_direct mysqli_fetch_fields mysqli_fetch_lengths mysqli_fetch_object mysqli_fetch_row mysqli_field_count mysqli_field_seek mysqli_field_tell mysqli_free_result mysqli_get_cache_stats mysqli_get_charset mysqli_get_client_info mysqli_get_client_stats mysqli_get_client_version mysqli_get_connection_stats mysqli_get_host_info mysqli_get_links_stats mysqli_get_metadata mysqli_get_proto_info mysqli_get_server_info mysqli_get_server_version mysqli_get_warnings mysqli_group_flag mysqli_info mysqli_init mysqli_init_command mysqli_insert_id mysqli_kill mysqli_more_results mysqli_multi_query mysqli_multiple_key_flag mysqli_need_data mysqli_next_result mysqli_no_data mysqli_no_default_value_flag mysqli_not_null_flag mysqli_num mysqli_num_fields mysqli_num_flag mysqli_num_rows mysqli_on_update_now_flag mysqli_opt_can_handle_expired_passwords mysqli_opt_connect_timeout mysqli_opt_int_and_float_native mysqli_opt_local_infile mysqli_opt_net_cmd_buffer_size mysqli_opt_net_read_buffer_size mysqli_opt_ssl_verify_server_cert mysqli_options mysqli_param_count mysqli_part_key_flag mysqli_ping mysqli_poll mysqli_prepare mysqli_pri_key_flag mysqli_query mysqli_read_default_file mysqli_read_default_group mysqli_real_connect mysqli_real_escape_string mysqli_real_query mysqli_reap_async_query mysqli_refresh mysqli_refresh_backup_log mysqli_refresh_grant mysqli_refresh_hosts mysqli_refresh_log mysqli_refresh_master mysqli_refresh_slave mysqli_refresh_status mysqli_refresh_tables mysqli_refresh_threads mysqli_release_savepoint mysqli_report mysqli_report_all mysqli_report_error mysqli_report_index mysqli_report_off mysqli_report_strict mysqli_rollback mysqli_savepoint mysqli_select_db mysqli_send_long_data mysqli_server_ps_out_params mysqli_server_public_key mysqli_server_query_no_good_index_used mysqli_server_query_no_index_used mysqli_server_query_was_slow mysqli_set_charset mysqli_set_charset_dir mysqli_set_charset_name mysqli_set_flag mysqli_set_local_infile_default mysqli_set_local_infile_handler mysqli_set_opt mysqli_sqlstate mysqli_ssl_set mysqli_stat mysqli_stmt_affected_rows mysqli_stmt_attr_cursor_type mysqli_stmt_attr_get mysqli_stmt_attr_prefetch_rows mysqli_stmt_attr_set mysqli_stmt_attr_update_max_length mysqli_stmt_bind_param mysqli_stmt_bind_result mysqli_stmt_close mysqli_stmt_data_seek mysqli_stmt_errno mysqli_stmt_error mysqli_stmt_error_list mysqli_stmt_execute mysqli_stmt_fetch mysqli_stmt_field_count mysqli_stmt_free_result mysqli_stmt_get_result mysqli_stmt_get_warnings mysqli_stmt_init mysqli_stmt_insert_id mysqli_stmt_more_results mysqli_stmt_next_result mysqli_stmt_num_rows mysqli_stmt_param_count mysqli_stmt_prepare mysqli_stmt_reset mysqli_stmt_result_metadata mysqli_stmt_send_long_data mysqli_stmt_sqlstate mysqli_stmt_store_result mysqli_store_result mysqli_store_result_copy_data mysqli_thread_id mysqli_thread_safe mysqli_timestamp_flag mysqli_trans_cor_and_chain mysqli_trans_cor_and_no_chain mysqli_trans_cor_no_release mysqli_trans_cor_release mysqli_trans_start_read_only mysqli_trans_start_read_write mysqli_trans_start_with_consistent_snapshot mysqli_type_bit mysqli_type_blob mysqli_type_char mysqli_type_date mysqli_type_datetime mysqli_type_decimal mysqli_type_double mysqli_type_enum mysqli_type_float mysqli_type_geometry mysqli_type_int24 mysqli_type_interval mysqli_type_long mysqli_type_long_blob mysqli_type_longlong mysqli_type_medium_blob mysqli_type_newdate mysqli_type_newdecimal mysqli_type_null mysqli_type_set mysqli_type_short mysqli_type_string mysqli_type_time mysqli_type_timestamp mysqli_type_tiny mysqli_type_tiny_blob mysqli_type_var_string mysqli_type_year mysqli_unique_key_flag mysqli_unsigned_flag mysqli_use_result mysqli_warning_count mysqli_zerofill_flag n_cs_precedes n_sep_by_space n_sign_posn namespace nan natcasesort natsort ncurses_addch ncurses_addchnstr ncurses_addchstr ncurses_addnstr ncurses_addstr ncurses_all_mouse_events ncurses_assume_default_colors ncurses_attroff ncurses_attron ncurses_attrset ncurses_baudrate ncurses_beep ncurses_bkgd ncurses_bkgdset ncurses_border ncurses_bottom_panel ncurses_button1_clicked ncurses_button1_double_clicked ncurses_button1_pressed ncurses_button1_released ncurses_button1_triple_clicked ncurses_button_alt ncurses_button_ctrl ncurses_button_shift ncurses_can_change_color ncurses_cbreak ncurses_clear ncurses_clrtobot ncurses_clrtoeol ncurses_color_black ncurses_color_blue ncurses_color_content ncurses_color_cyan ncurses_color_green ncurses_color_magenta ncurses_color_red ncurses_color_set ncurses_color_white ncurses_color_yellow ncurses_curs_set ncurses_def_prog_mode ncurses_def_shell_mode ncurses_define_key ncurses_del_panel ncurses_delay_output ncurses_delch ncurses_deleteln ncurses_delwin ncurses_doupdate ncurses_echo ncurses_echochar ncurses_end ncurses_erase ncurses_erasechar ncurses_filter ncurses_flash ncurses_flushinp ncurses_getch ncurses_getmaxyx ncurses_getmouse ncurses_getyx ncurses_halfdelay ncurses_has_colors ncurses_has_ic ncurses_has_il ncurses_has_key ncurses_hide_panel ncurses_hline ncurses_inch ncurses_init ncurses_init_color ncurses_init_pair ncurses_insch ncurses_insdelln ncurses_insertln ncurses_insstr ncurses_instr ncurses_isendwin ncurses_key_a1 ncurses_key_a3 ncurses_key_b2 ncurses_key_backspace ncurses_key_beg ncurses_key_btab ncurses_key_c1 ncurses_key_c3 ncurses_key_cancel ncurses_key_catab ncurses_key_clear ncurses_key_close ncurses_key_command ncurses_key_copy ncurses_key_create ncurses_key_ctab ncurses_key_dc ncurses_key_dl ncurses_key_down ncurses_key_eic ncurses_key_end ncurses_key_eol ncurses_key_eos ncurses_key_exit ncurses_key_f0 ncurses_key_find ncurses_key_help ncurses_key_home ncurses_key_ic ncurses_key_il ncurses_key_left ncurses_key_ll ncurses_key_mark ncurses_key_max ncurses_key_message ncurses_key_mouse ncurses_key_move ncurses_key_next ncurses_key_npage ncurses_key_open ncurses_key_options ncurses_key_ppage ncurses_key_previous ncurses_key_print ncurses_key_redo ncurses_key_reference ncurses_key_refresh ncurses_key_replace ncurses_key_reset ncurses_key_restart ncurses_key_resume ncurses_key_right ncurses_key_save ncurses_key_sbeg ncurses_key_scancel ncurses_key_scommand ncurses_key_scopy ncurses_key_screate ncurses_key_sdc ncurses_key_sdl ncurses_key_select ncurses_key_send ncurses_key_seol ncurses_key_sexit ncurses_key_sf ncurses_key_sfind ncurses_key_shelp ncurses_key_shome ncurses_key_sic ncurses_key_sleft ncurses_key_smessage ncurses_key_smove ncurses_key_snext ncurses_key_soptions ncurses_key_sprevious ncurses_key_sprint ncurses_key_sr ncurses_key_sredo ncurses_key_sreplace ncurses_key_sreset ncurses_key_sright ncurses_key_srsume ncurses_key_ssave ncurses_key_ssuspend ncurses_key_stab ncurses_key_undo ncurses_key_up ncurses_keyok ncurses_keypad ncurses_killchar ncurses_longname ncurses_meta ncurses_mouse_trafo ncurses_mouseinterval ncurses_mousemask ncurses_move ncurses_move_panel ncurses_mvaddch ncurses_mvaddchnstr ncurses_mvaddchstr ncurses_mvaddnstr ncurses_mvaddstr ncurses_mvcur ncurses_mvdelch ncurses_mvgetch ncurses_mvhline ncurses_mvinch ncurses_mvvline ncurses_mvwaddstr ncurses_napms ncurses_new_panel ncurses_newpad ncurses_newwin ncurses_nl ncurses_nocbreak ncurses_noecho ncurses_nonl ncurses_noqiflush ncurses_noraw ncurses_pair_content
 ncurses_panel_above ncurses_panel_below ncurses_panel_window ncurses_pnoutrefresh ncurses_prefresh ncurses_putp ncurses_qiflush ncurses_raw ncurses_refresh ncurses_replace_panel ncurses_report_mouse_position ncurses_reset_prog_mode ncurses_reset_shell_mode ncurses_resetty ncurses_savetty ncurses_scr_dump ncurses_scr_init ncurses_scr_restore ncurses_scr_set ncurses_scrl ncurses_show_panel ncurses_slk_attr ncurses_slk_attroff ncurses_slk_attron ncurses_slk_attrset ncurses_slk_clear ncurses_slk_color ncurses_slk_init ncurses_slk_noutrefresh ncurses_slk_refresh ncurses_slk_restore ncurses_slk_set ncurses_slk_touch ncurses_standend ncurses_standout ncurses_start_color ncurses_termattrs ncurses_termname ncurses_timeout ncurses_top_panel ncurses_typeahead ncurses_ungetch ncurses_ungetmouse ncurses_update_panels ncurses_use_default_colors ncurses_use_env ncurses_use_extended_names ncurses_vidattr ncurses_vline ncurses_waddch ncurses_waddstr ncurses_wattroff ncurses_wattron ncurses_wattrset ncurses_wborder ncurses_wclear ncurses_wcolor_set ncurses_werase ncurses_wgetch ncurses_whline ncurses_wmouse_trafo ncurses_wmove ncurses_wnoutrefresh ncurses_wrefresh ncurses_wstandend ncurses_wstandout ncurses_wvline negative_sign new newt_anchor_bottom newt_anchor_left newt_anchor_right newt_anchor_top newt_arg_append newt_arg_last newt_bell newt_button newt_button_bar newt_centered_window newt_checkbox newt_checkbox_get_value newt_checkbox_set_flags newt_checkbox_set_value newt_checkbox_tree newt_checkbox_tree_add_item newt_checkbox_tree_find_item newt_checkbox_tree_get_current newt_checkbox_tree_get_entry_value newt_checkbox_tree_get_multi_selection newt_checkbox_tree_get_selection newt_checkbox_tree_multi newt_checkbox_tree_set_current newt_checkbox_tree_set_entry newt_checkbox_tree_set_entry_value newt_checkbox_tree_set_width newt_checkboxtree_collapsed newt_checkboxtree_expanded newt_checkboxtree_hide_box newt_checkboxtree_selected newt_checkboxtree_unselectable newt_checkboxtree_unselected newt_clear_key_buffer newt_cls newt_colorset_actbutton newt_colorset_actcheckbox newt_colorset_actlistbox newt_colorset_actsellistbox newt_colorset_acttextbox newt_colorset_border newt_colorset_button newt_colorset_checkbox newt_colorset_compactbutton newt_colorset_disentry newt_colorset_emptyscale newt_colorset_entry newt_colorset_fullscale newt_colorset_helpline newt_colorset_label newt_colorset_listbox newt_colorset_root newt_colorset_roottext newt_colorset_sellistbox newt_colorset_shadow newt_colorset_textbox newt_colorset_title newt_colorset_window newt_compact_button newt_component_add_callback newt_component_takes_focus newt_create_grid newt_cursor_off newt_cursor_on newt_delay newt_draw_form newt_draw_root_text newt_entry newt_entry_disabled newt_entry_get_value newt_entry_hidden newt_entry_returnexit newt_entry_scroll newt_entry_set newt_entry_set_filter newt_entry_set_flags newt_exit_component newt_exit_fdready newt_exit_hotkey newt_exit_timer newt_fd_except newt_fd_read newt_fd_write newt_finished newt_flag_border newt_flag_checkbox newt_flag_disabled newt_flag_hidden newt_flag_multiple newt_flag_nof12 newt_flag_password newt_flag_returnexit newt_flag_scroll newt_flag_selected newt_flag_showcursor newt_flag_wrap newt_flags_reset newt_flags_set newt_flags_toggle newt_form newt_form_add_component newt_form_add_components newt_form_add_hot_key newt_form_destroy newt_form_get_current newt_form_nof12 newt_form_run newt_form_set_background newt_form_set_height newt_form_set_size newt_form_set_timer newt_form_set_width newt_form_watch_fd newt_get_screen_size newt_grid_add_components_to_form newt_grid_basic_window newt_grid_component newt_grid_empty newt_grid_flag_growx newt_grid_flag_growy newt_grid_free newt_grid_get_size newt_grid_h_close_stacked newt_grid_h_stacked newt_grid_place newt_grid_set_field newt_grid_simple_window newt_grid_subgrid newt_grid_v_close_stacked newt_grid_v_stacked newt_grid_wrapped_window newt_grid_wrapped_window_at newt_init newt_key_bkspc newt_key_delete newt_key_down newt_key_end newt_key_enter newt_key_escape newt_key_extra_base newt_key_f1 newt_key_f10 newt_key_f11 newt_key_f12 newt_key_f2 newt_key_f3 newt_key_f4 newt_key_f5 newt_key_f6 newt_key_f7 newt_key_f8 newt_key_f9 newt_key_home newt_key_insert newt_key_left newt_key_pgdn newt_key_pgup newt_key_resize newt_key_return newt_key_right newt_key_suspend newt_key_tab newt_key_untab newt_key_up newt_label newt_label_set_text newt_listbox newt_listbox_append_entry newt_listbox_clear newt_listbox_clear_selection newt_listbox_delete_entry newt_listbox_get_current newt_listbox_get_selection newt_listbox_insert_entry newt_listbox_item_count newt_listbox_returnexit newt_listbox_select_item newt_listbox_set_current newt_listbox_set_current_by_key newt_listbox_set_data newt_listbox_set_entry newt_listbox_set_width newt_listitem newt_listitem_get_data newt_listitem_set newt_open_window newt_pop_help_line newt_pop_window newt_push_help_line newt_radio_get_current newt_radiobutton newt_redraw_help_line newt_reflow_text newt_refresh newt_resize_screen newt_resume newt_run_form newt_scale newt_scale_set newt_scrollbar_set newt_set_help_callback newt_set_suspend_callback newt_suspend newt_textbox newt_textbox_get_num_lines newt_textbox_reflowed newt_textbox_scroll newt_textbox_set_height newt_textbox_set_text newt_textbox_wrap newt_vertical_scrollbar newt_wait_for_key newt_win_choice newt_win_entries newt_win_menu newt_win_message newt_win_messagev newt_win_ternary next ngettext nil nl2br nl_langinfo noexpr norm_ignorecase norm_ignorekanatype norm_ignorekashida norm_ignorenonspace norm_ignoresymbols norm_ignorewidth normalizer_is_normalized normalizer_normalize nostr nthmac null number_format numfmt_create numfmt_format numfmt_format_currency numfmt_get_attribute numfmt_get_error_code numfmt_get_error_message numfmt_get_locale numfmt_get_pattern numfmt_get_symbol numfmt_get_text_attribute numfmt_parse numfmt_parse_currency numfmt_set_attribute numfmt_set_pattern numfmt_set_symbol numfmt_set_text_attribute o_append o_async o_creat o_excl o_ndelay o_noctty o_nonblock o_rdonly o_rdwr o_sync o_trunc o_wronly ob_clean ob_deflatehandler ob_end_clean ob_end_flush ob_etaghandler ob_flush ob_get_clean ob_get_contents ob_get_flush ob_get_length ob_get_level ob_get_status ob_gzhandler ob_iconv_handler ob_implicit_flush ob_inflatehandler ob_list_handlers ob_start ob_tidyhandler object oci_assoc oci_b_bfile oci_b_bin oci_b_blob oci_b_bol oci_b_cfilee oci_b_clob oci_b_cursor oci_b_int oci_b_nty oci_b_num oci_b_rowid oci_bind_array_by_name oci_bind_by_name oci_both oci_cancel oci_client_version oci_close oci_commit oci_commit_on_success oci_connect oci_cred_ext oci_d_file oci_d_lob oci_d_rowid oci_default oci_define_by_name oci_describe_only oci_dtype_file oci_dtype_lob oci_dtype_rowid oci_error oci_exact_fetch oci_execute oci_fetch oci_fetch_all oci_fetch_array oci_fetch_assoc oci_fetch_object oci_fetch_row oci_fetchstatement_by_column oci_fetchstatement_by_row oci_field_is_null oci_field_name oci_field_precision oci_field_scale oci_field_size oci_field_type oci_field_type_raw oci_free_descriptor oci_free_statement oci_get_implicit_resultset oci_internal_debug oci_lob_buffer_free oci_lob_copy oci_lob_is_equal oci_new_collection oci_new_connect oci_new_cursor oci_new_descriptor oci_no_auto_commit oci_num oci_num_fields oci_num_rows oci_parse oci_password_change oci_pconnect oci_result oci_return_lobs oci_return_nulls oci_rollback oci_seek_cur oci_seek_end oci_seek_set oci_server_version oci_set_action oci_set_client_identifier oci_set_client_info oci_set_edition oci_set_module_name oci_set_prefetch oci_statement_type oci_sysdate oci_sysdba oci_sysoper oci_temp_blob oci_temp_clob ocibindbyname ocicolumnisnull ocicolumnname ocicolumnsize ocicolumntype ocicommit ocidefinebyname ocierror ociexecute ocifetch ocifetchinto ocifetchstatement ocifreestatement ocilogoff ocilogon ocinewcursor ocinewdescriptor ocinlogon ocinumcols ociparse ociplogon ociresult ocirollback ocirowcount ociserverversion ocistatementtype octdec odbc_autocommit odbc_binmode odbc_binmode_convert odbc_binmode_passthru odbc_binmode_return odbc_close odbc_close_all odbc_columnprivileges odbc_columns odbc_commit odbc_connect odbc_cursor odbc_data_source odbc_do odbc_error odbc_errormsg odbc_exec odbc_execute odbc_fetch_array odbc_fetch_into odbc_fetch_object odbc_fetch_row odbc_field_len odbc_field_name odbc_field_num odbc_field_precision odbc_field_scale odbc_field_type odbc_foreignkeys odbc_free_result odbc_gettypeinfo odbc_longreadlen odbc_next_result odbc_num_fields odbc_num_rows odbc_pconnect odbc_prepare odbc_primarykeys odbc_procedurecolumns odbc_procedures odbc_result odbc_result_all odbc_rollback odbc_setoption odbc_specialcolumns odbc_statistics odbc_tableprivileges odbc_tables odbc_type oggvorbis_pcm_s16_be oggvorbis_pcm_s16_le oggvorbis_pcm_s8 oggvorbis_pcm_u16_be oggvorbis_pcm_u16_le oggvorbis_pcm_u8 old_function op_anonymous op_debug op_expunge op_halfopen op_prototype op_readonly op_secure op_shortcache op_silent opcache_compile_file opcache_get_configuration opcache_get_status opcache_invalidate opcache_is_script_cached opcache_reset openal_buffer_create openal_buffer_data openal_buffer_destroy openal_buffer_get openal_buffer_loadwav openal_context_create openal_context_current openal_context_destroy openal_context_process openal_context_suspend openal_device_close openal_device_open openal_listener_get openal_listener_set openal_source_create openal_source_destroy openal_source_get openal_source_pause openal_source_play openal_source_rewind openal_source_set openal_source_stop openal_stream opendir openlog openssl_algo_dss1 openssl_algo_md4 openssl_algo_md5 openssl_algo_rmd160 openssl_algo_sha1
 openssl_algo_sha224 openssl_algo_sha256 openssl_algo_sha384 openssl_algo_sha512 openssl_cipher_3des openssl_cipher_aes_128_cbc openssl_cipher_aes_192_cbc openssl_cipher_aes_256_cbc openssl_cipher_des openssl_cipher_iv_length openssl_cipher_rc2_128 openssl_cipher_rc2_40 openssl_cipher_rc2_64 openssl_csr_export openssl_csr_export_to_file openssl_csr_get_public_key openssl_csr_get_subject openssl_csr_new openssl_csr_sign openssl_decrypt openssl_default_stream_ciphers openssl_dh_compute_key openssl_digest openssl_encrypt openssl_error_string openssl_free_key openssl_get_cert_locations openssl_get_cipher_methods openssl_get_md_methods openssl_get_privatekey openssl_get_publickey openssl_keytype_dh openssl_keytype_dsa openssl_keytype_ec openssl_keytype_rsa openssl_no_padding openssl_open openssl_pbkdf2 openssl_pkcs12_export openssl_pkcs12_export_to_file openssl_pkcs12_read openssl_pkcs1_oaep_padding openssl_pkcs1_padding openssl_pkcs7_decrypt openssl_pkcs7_encrypt openssl_pkcs7_sign openssl_pkcs7_verify openssl_pkey_export openssl_pkey_export_to_file openssl_pkey_free openssl_pkey_get_details openssl_pkey_get_private openssl_pkey_get_public openssl_pkey_new openssl_private_decrypt openssl_private_encrypt openssl_public_decrypt openssl_public_encrypt openssl_random_pseudo_bytes openssl_raw_data openssl_seal openssl_sign openssl_spki_export openssl_spki_export_challenge openssl_spki_new openssl_spki_verify openssl_sslv23_padding openssl_tlsext_server_name openssl_verify openssl_version_number openssl_version_text openssl_x509_check_private_key openssl_x509_checkpurpose openssl_x509_export openssl_x509_export_to_file openssl_x509_fingerprint openssl_x509_free openssl_x509_parse openssl_x509_read openssl_zero_padding or ord output_add_rewrite_var output_reset_rewrite_vars override_function p_cs_precedes p_sep_by_space p_sign_posn pack parent parse_ini_file parse_ini_string parse_str parse_url parsekit_compile_file parsekit_compile_string parsekit_extended_value parsekit_func_arginfo parsekit_is_const parsekit_is_tmp_var parsekit_is_unused parsekit_is_var parsekit_quiet parsekit_result_const parsekit_result_ea_type parsekit_result_jmp_addr parsekit_result_oparray parsekit_result_opline parsekit_result_var parsekit_simple parsekit_usage_unknown parsekit_zend_add parsekit_zend_add_array_element parsekit_zend_add_char parsekit_zend_add_interface parsekit_zend_add_string parsekit_zend_add_var parsekit_zend_assign parsekit_zend_assign_add parsekit_zend_assign_bw_and parsekit_zend_assign_bw_or parsekit_zend_assign_bw_xor parsekit_zend_assign_concat parsekit_zend_assign_dim parsekit_zend_assign_div parsekit_zend_assign_mod parsekit_zend_assign_mul parsekit_zend_assign_obj parsekit_zend_assign_ref parsekit_zend_assign_sl parsekit_zend_assign_sr parsekit_zend_assign_sub parsekit_zend_begin_silence parsekit_zend_bool parsekit_zend_bool_not parsekit_zend_bool_xor parsekit_zend_brk parsekit_zend_bw_and parsekit_zend_bw_not parsekit_zend_bw_or parsekit_zend_bw_xor parsekit_zend_case parsekit_zend_cast parsekit_zend_catch parsekit_zend_clone parsekit_zend_concat parsekit_zend_cont parsekit_zend_declare_class parsekit_zend_declare_function parsekit_zend_declare_inherited_class parsekit_zend_div parsekit_zend_do_fcall parsekit_zend_do_fcall_by_name parsekit_zend_echo parsekit_zend_end_silence parsekit_zend_eval_code parsekit_zend_exit parsekit_zend_ext_fcall_begin parsekit_zend_ext_fcall_end parsekit_zend_ext_nop parsekit_zend_ext_stmt parsekit_zend_fe_fetch parsekit_zend_fe_reset parsekit_zend_fetch_class parsekit_zend_fetch_constant parsekit_zend_fetch_dim_func_arg parsekit_zend_fetch_dim_is parsekit_zend_fetch_dim_r parsekit_zend_fetch_dim_rw parsekit_zend_fetch_dim_tmp_var parsekit_zend_fetch_dim_unset parsekit_zend_fetch_dim_w parsekit_zend_fetch_func_arg parsekit_zend_fetch_is parsekit_zend_fetch_obj_func_arg parsekit_zend_fetch_obj_is parsekit_zend_fetch_obj_r parsekit_zend_fetch_obj_rw parsekit_zend_fetch_obj_unset parsekit_zend_fetch_obj_w parsekit_zend_fetch_r parsekit_zend_fetch_rw parsekit_zend_fetch_unset parsekit_zend_fetch_w parsekit_zend_free parsekit_zend_handle_exception parsekit_zend_import_class parsekit_zend_import_const parsekit_zend_import_function parsekit_zend_include_or_eval parsekit_zend_init_array parsekit_zend_init_ctor_call parsekit_zend_init_fcall_by_name parsekit_zend_init_method_call parsekit_zend_init_static_method_call parsekit_zend_init_string parsekit_zend_instanceof parsekit_zend_internal_class parsekit_zend_internal_function parsekit_zend_is_equal parsekit_zend_is_identical parsekit_zend_is_not_equal parsekit_zend_is_not_identical parsekit_zend_is_smaller parsekit_zend_is_smaller_or_equal parsekit_zend_isset_isempty parsekit_zend_isset_isempty_dim_obj parsekit_zend_isset_isempty_prop_obj parsekit_zend_isset_isempty_var parsekit_zend_jmp parsekit_zend_jmp_no_ctor parsekit_zend_jmpnz parsekit_zend_jmpnz_ex parsekit_zend_jmpz parsekit_zend_jmpz_ex parsekit_zend_jmpznz parsekit_zend_mod parsekit_zend_mul parsekit_zend_new parsekit_zend_nop parsekit_zend_op_data parsekit_zend_overloaded_function parsekit_zend_overloaded_function_temporary parsekit_zend_post_dec parsekit_zend_post_dec_obj parsekit_zend_post_inc parsekit_zend_post_inc_obj parsekit_zend_pre_dec parsekit_zend_pre_dec_obj parsekit_zend_pre_inc parsekit_zend_pre_inc_obj parsekit_zend_print parsekit_zend_qm_assign parsekit_zend_raise_abstract_error parsekit_zend_recv parsekit_zend_recv_init parsekit_zend_return parsekit_zend_send_ref parsekit_zend_send_val parsekit_zend_send_var parsekit_zend_send_var_no_ref parsekit_zend_sl parsekit_zend_sr parsekit_zend_sub parsekit_zend_switch_free parsekit_zend_throw parsekit_zend_ticks parsekit_zend_unset_dim_obj parsekit_zend_unset_var parsekit_zend_user_class parsekit_zend_user_function parsekit_zend_verify_abstract_class passthru password_bcrypt password_bcrypt_default_cost password_default password_get_info password_hash password_needs_rehash password_verify path_separator pathinfo pathinfo_basename pathinfo_dirname pathinfo_extension pathinfo_filename pclose pcntl_alarm pcntl_errno pcntl_exec pcntl_fork pcntl_get_last_error pcntl_getpriority pcntl_setpriority pcntl_signal pcntl_signal_dispatch pcntl_sigprocmask pcntl_sigtimedwait pcntl_sigwaitinfo pcntl_strerror pcntl_wait pcntl_waitpid pcntl_wexitstatus pcntl_wifexited pcntl_wifsignaled pcntl_wifstopped pcntl_wstopsig pcntl_wtermsig pcre_version pdf_activate_item pdf_add_annotation pdf_add_bookmark pdf_add_launchlink pdf_add_locallink pdf_add_nameddest pdf_add_note pdf_add_outline pdf_add_pdflink pdf_add_table_cell pdf_add_textflow pdf_add_thumbnail pdf_add_weblink pdf_arc pdf_arcn pdf_attach_file pdf_begin_document pdf_begin_font pdf_begin_glyph pdf_begin_item pdf_begin_layer pdf_begin_page pdf_begin_page_ext pdf_begin_pattern pdf_begin_template pdf_begin_template_ext pdf_circle pdf_clip pdf_close pdf_close_image pdf_close_pdi pdf_close_pdi_page pdf_closepath pdf_closepath_fill_stroke pdf_closepath_stroke pdf_concat pdf_continue_text pdf_create_3dview pdf_create_action pdf_create_annotation pdf_create_bookmark pdf_create_field pdf_create_fieldgroup pdf_create_gstate pdf_create_pvf pdf_create_textflow pdf_curveto pdf_define_layer pdf_delete pdf_delete_pvf pdf_delete_table pdf_delete_textflow pdf_encoding_set_char pdf_end_document pdf_end_font pdf_end_glyph pdf_end_item pdf_end_layer pdf_end_page pdf_end_page_ext pdf_end_pattern pdf_end_template pdf_endpath pdf_fill pdf_fill_imageblock pdf_fill_pdfblock pdf_fill_stroke pdf_fill_textblock pdf_findfont pdf_fit_image pdf_fit_pdi_page pdf_fit_table pdf_fit_textflow pdf_fit_textline pdf_get_apiname pdf_get_buffer pdf_get_errmsg pdf_get_errnum pdf_get_font pdf_get_fontname pdf_get_fontsize pdf_get_image_height pdf_get_image_width pdf_get_majorversion pdf_get_minorversion pdf_get_parameter pdf_get_pdi_parameter pdf_get_pdi_value pdf_get_value pdf_info_font pdf_info_matchbox pdf_info_table pdf_info_textflow pdf_info_textline pdf_initgraphics pdf_lineto pdf_load_3ddata pdf_load_font pdf_load_iccprofile pdf_load_image pdf_makespotcolor pdf_moveto pdf_new pdf_open_ccitt pdf_open_file pdf_open_gif pdf_open_image pdf_open_image_file pdf_open_jpeg pdf_open_memory_image pdf_open_pdi pdf_open_pdi_document pdf_open_pdi_page pdf_open_tiff pdf_pcos_get_number pdf_pcos_get_stream pdf_pcos_get_string pdf_place_image pdf_place_pdi_page pdf_process_pdi pdf_rect pdf_restore pdf_resume_page pdf_rotate pdf_save pdf_scale pdf_set_border_color pdf_set_border_dash pdf_set_border_style pdf_set_char_spacing pdf_set_duration pdf_set_gstate pdf_set_horiz_scaling pdf_set_info pdf_set_info_author pdf_set_info_creator pdf_set_info_keywords pdf_set_info_subject pdf_set_info_title pdf_set_layer_dependency pdf_set_leading pdf_set_parameter pdf_set_text_matrix pdf_set_text_pos pdf_set_text_rendering pdf_set_text_rise pdf_set_value pdf_set_word_spacing pdf_setcolor pdf_setdash pdf_setdashpattern pdf_setflat pdf_setfont pdf_setgray pdf_setgray_fill pdf_setgray_stroke pdf_setlinecap pdf_setlinejoin pdf_setlinewidth pdf_setmatrix pdf_setmiterlimit pdf_setpolydash pdf_setrgbcolor pdf_setrgbcolor_fill pdf_setrgbcolor_stroke pdf_shading pdf_shading_pattern pdf_shfill pdf_show pdf_show_boxed pdf_show_xy pdf_skew pdf_stringwidth pdf_stroke pdf_suspend_page pdf_translate pdf_utf16_to_utf8 pdf_utf32_to_utf16 pdf_utf8_to_utf16 pdo_drivers pear_extension_dir pear_install_dir pfsockopen pg_affected_rows pg_cancel_query pg_client_encoding pg_clientencoding pg_close pg_cmdtuples pg_connect pg_connect_poll pg_connection_busy pg_connection_reset pg_connection_status pg_consume_input pg_convert pg_copy_from pg_copy_to pg_dbname pg_delete pg_end_copy pg_errormessage pg_escape_bytea pg_escape_identifier pg_escape_literal pg_escape_string pg_exec
 pg_execute pg_fetch_all pg_fetch_all_columns pg_fetch_array pg_fetch_assoc pg_fetch_object pg_fetch_result pg_fetch_row pg_field_is_null pg_field_name pg_field_num pg_field_prtlen pg_field_size pg_field_table pg_field_type pg_field_type_oid pg_fieldisnull pg_fieldname pg_fieldnum pg_fieldprtlen pg_fieldsize pg_fieldtype pg_flush pg_free_result pg_freeresult pg_get_notify pg_get_pid pg_get_result pg_getlastoid pg_host pg_insert pg_last_error pg_last_notice pg_last_oid pg_lo_close pg_lo_create pg_lo_export pg_lo_import pg_lo_open pg_lo_read pg_lo_read_all pg_lo_seek pg_lo_tell pg_lo_truncate pg_lo_unlink pg_lo_write pg_loclose pg_locreate pg_loexport pg_loimport pg_loopen pg_loread pg_loreadall pg_lounlink pg_lowrite pg_meta_data pg_num_fields pg_num_rows pg_numfields pg_numrows pg_options pg_parameter_status pg_pconnect pg_ping pg_port pg_prepare pg_put_line pg_query pg_query_params pg_result pg_result_error pg_result_error_field pg_result_seek pg_result_status pg_select pg_send_execute pg_send_prepare pg_send_query pg_send_query_params pg_set_client_encoding pg_set_error_verbosity pg_setclientencoding pg_socket pg_trace pg_transaction_status pg_tty pg_unescape_bytea pg_untrace pg_update pg_version pgsql_assoc pgsql_bad_response pgsql_both pgsql_command_ok pgsql_connect_async pgsql_connect_force_new pgsql_connection_auth_ok pgsql_connection_awaiting_response pgsql_connection_bad pgsql_connection_made pgsql_connection_ok pgsql_connection_setenv pgsql_connection_started pgsql_conv_force_null pgsql_conv_ignore_default pgsql_conv_ignore_not_null pgsql_copy_in pgsql_copy_out pgsql_diag_context pgsql_diag_internal_position pgsql_diag_internal_query pgsql_diag_message_detail pgsql_diag_message_hint pgsql_diag_message_primary pgsql_diag_severity pgsql_diag_source_file pgsql_diag_source_function pgsql_diag_source_line pgsql_diag_sqlstate pgsql_diag_statement_position pgsql_dml_async pgsql_dml_escape pgsql_dml_exec pgsql_dml_no_conv pgsql_dml_string pgsql_empty_query pgsql_errors_default pgsql_errors_terse pgsql_errors_verbose pgsql_fatal_error pgsql_libpq_version pgsql_libpq_version_str pgsql_nonfatal_error pgsql_num pgsql_polling_active pgsql_polling_failed pgsql_polling_ok pgsql_polling_reading pgsql_polling_writing pgsql_seek_cur pgsql_seek_end pgsql_seek_set pgsql_status_long pgsql_status_string pgsql_transaction_active pgsql_transaction_idle pgsql_transaction_inerror pgsql_transaction_intrans pgsql_transaction_unknown pgsql_tuples_ok php_binary php_binary_read php_bindir php_check_syntax php_config_file_path php_config_file_scan_dir php_datadir php_debug php_egg_logo_guid php_eol php_extension_dir php_extra_version php_ini_loaded_file php_ini_scanned_files php_int_max php_int_size php_libdir php_localstatedir php_logo_guid php_major_version php_mandir php_maxpathlen php_minor_version php_normal_read php_os php_output_handler_clean php_output_handler_cleanable php_output_handler_cont php_output_handler_disabled php_output_handler_end php_output_handler_final php_output_handler_flush php_output_handler_flushable php_output_handler_removable php_output_handler_start php_output_handler_started php_output_handler_stdflags php_output_handler_write php_prefix php_query_rfc1738 php_query_rfc3986 php_real_logo_guid php_release_version php_round_half_down php_round_half_even php_round_half_odd php_round_half_up php_sapi php_sapi_name php_session_active php_session_disabled php_session_none php_shlib_suffix php_strip_whitespace php_svn_auth_param_ignore_ssl_verify_errors php_sysconfdir php_uname php_url_fragment php_url_host php_url_pass php_url_path php_url_port php_url_query php_url_scheme php_url_user php_version php_version_id php_windows_nt_domain_controller php_windows_nt_server php_windows_nt_workstation php_windows_version_build php_windows_version_major php_windows_version_minor php_windows_version_platform php_windows_version_producttype php_windows_version_sp_major php_windows_version_sp_minor php_windows_version_suitemask php_zts phpcredits phpinfo phpversion pi pkcs7_binary pkcs7_detached pkcs7_noattr pkcs7_nocerts pkcs7_nochain pkcs7_nointern pkcs7_nosigs pkcs7_noverify pkcs7_text pm_str png2wbmp png_all_filters png_filter_avg png_filter_none png_filter_paeth png_filter_sub png_filter_up png_no_filter poll_err poll_hup poll_in poll_msg poll_out poll_pri popen pos positive_sign posix_access posix_ctermid posix_errno posix_f_ok posix_get_last_error posix_getcwd posix_getegid posix_geteuid posix_getgid posix_getgrgid posix_getgrnam posix_getgroups posix_getlogin posix_getpgid posix_getpgrp posix_getpid posix_getppid posix_getpwnam posix_getpwuid posix_getrlimit posix_getsid posix_getuid posix_initgroups posix_isatty posix_kill posix_mkfifo posix_mknod posix_r_ok posix_s_ifblk posix_s_ifchr posix_s_ififo posix_s_ifreg posix_s_ifsock posix_setegid posix_seteuid posix_setgid posix_setpgid posix_setrlimit posix_setsid posix_setuid posix_strerror posix_times posix_ttyname posix_uname posix_w_ok posix_x_ok pow preg_backtrack_limit_error preg_bad_utf8_error preg_bad_utf8_offset_error preg_filter preg_grep preg_grep_invert preg_internal_error preg_last_error preg_match preg_match_all preg_no_error preg_offset_capture preg_pattern_order preg_quote preg_recursion_limit_error preg_replace preg_replace_callback preg_replace_callback_array preg_set_order preg_split preg_split_delim_capture preg_split_no_empty preg_split_offset_capture prev print print_r printf private proc_close proc_get_status proc_nice proc_open proc_terminate prof_trace property_exists protected ps_add_bookmark ps_add_launchlink ps_add_locallink ps_add_note ps_add_pdflink ps_add_weblink ps_arc ps_arcn ps_begin_page ps_begin_pattern ps_begin_template ps_circle ps_clip ps_close ps_close_image ps_closepath ps_closepath_stroke ps_continue_text ps_curveto ps_delete ps_end_page ps_end_pattern ps_end_template ps_fill ps_fill_stroke ps_findfont ps_get_buffer ps_get_parameter ps_get_value ps_hyphenate ps_include_file ps_linecap_butt ps_linecap_round ps_linecap_squared ps_linejoin_bevel ps_linejoin_miter ps_linejoin_round ps_lineto ps_makespotcolor ps_moveto ps_new ps_open_file ps_open_image ps_open_image_file ps_open_memory_image ps_place_image ps_rect ps_restore ps_rotate ps_save ps_scale ps_set_border_color ps_set_border_dash ps_set_border_style ps_set_info ps_set_parameter ps_set_text_pos ps_set_value ps_setcolor ps_setdash ps_setflat ps_setfont ps_setgray ps_setlinecap ps_setlinejoin ps_setlinewidth ps_setmiterlimit ps_setoverprintmode ps_setpolydash ps_shading ps_shading_pattern ps_shfill ps_show ps_show2 ps_show_boxed ps_show_xy ps_show_xy2 ps_string_geometry ps_stringwidth ps_stroke ps_symbol ps_symbol_name ps_symbol_width ps_translate psfs_err_fatal psfs_feed_me psfs_flag_flush_close psfs_flag_flush_inc psfs_flag_normal psfs_pass_on pspell_add_to_personal pspell_add_to_session pspell_bad_spellers pspell_check pspell_clear_session pspell_config_create pspell_config_data_dir pspell_config_dict_dir pspell_config_ignore pspell_config_mode pspell_config_personal pspell_config_repl pspell_config_runtogether pspell_config_save_repl pspell_fast pspell_new pspell_new_config pspell_new_personal pspell_normal pspell_run_together pspell_save_wordlist pspell_store_replacement pspell_suggest pthreads_allow_headers pthreads_inherit_all pthreads_inherit_classes pthreads_inherit_comments pthreads_inherit_constants pthreads_inherit_functions pthreads_inherit_includes pthreads_inherit_ini pthreads_inherit_none public putenv px_close px_create_fp px_date2string px_delete px_delete_record px_field_alpha px_field_autoinc px_field_bcd px_field_blob px_field_bytes px_field_currency px_field_date px_field_fmtmemoblob px_field_graphic px_field_logical px_field_long px_field_memoblob px_field_number px_field_ole px_field_short px_field_time px_field_timestamp px_file_inc_sec_index px_file_inc_sec_index_g px_file_index_db px_file_non_inc_sec_index px_file_non_inc_sec_index_g px_file_non_index_db px_file_prim_index px_file_sec_index px_file_sec_index_g px_get_field px_get_info px_get_parameter px_get_record px_get_schema px_get_value px_insert_record px_keytolower px_keytoupper px_new px_numfields px_numrecords px_open_fp px_put_record px_retrieve_record px_set_blob_file px_set_parameter px_set_tablename px_set_targetencoding px_set_value px_timestamp2string px_update_record quoted_printable_decode quoted_printable_encode quotemeta rad2deg radius_access_accept radius_access_challenge radius_access_reject radius_access_request radius_accounting_off radius_accounting_on radius_accounting_request radius_accounting_response radius_acct_authentic radius_acct_delay_time radius_acct_input_octets radius_acct_input_packets radius_acct_link_count radius_acct_multi_session_id radius_acct_open radius_acct_output_octets radius_acct_output_packets radius_acct_session_id radius_acct_session_time radius_acct_status_type radius_acct_terminate_cause radius_add_server radius_administrative radius_adsl_cap radius_adsl_dmt radius_arap radius_async radius_auth_local radius_auth_open radius_auth_radius radius_auth_remote radius_authenticate_only radius_cable radius_callback_framed radius_callback_id radius_callback_login radius_callback_nas_prompt radius_callback_number radius_called_station_id radius_calling_station_id radius_chap_challenge radius_chap_password radius_class radius_close radius_coa_ack radius_coa_nak radius_coa_request radius_comp_ipxhdr radius_comp_none radius_comp_stac_lzs radius_comp_vj radius_config radius_connect_info radius_create_request radius_cvt_addr radius_cvt_int radius_cvt_string radius_demangle radius_demangle_mppe_key radius_disconnect_ack radius_disconnect_nak radius_disconnect_request radius_ethernet radius_filter_id radius_framed radius_framed_appletalk_link radius_framed_appletalk_network radius_framed_appletalk_zone
 radius_framed_compression radius_framed_ip_address radius_framed_ip_netmask radius_framed_ipx_network radius_framed_mtu radius_framed_protocol radius_framed_route radius_framed_routing radius_g_3_fax radius_gandalf radius_get_attr radius_get_tagged_attr_data radius_get_tagged_attr_tag radius_get_vendor_attr radius_hdlc_clear_channel radius_idle_timeout radius_idsl radius_isdn_async_v110 radius_isdn_async_v120 radius_isdn_sync radius_login radius_login_ip_host radius_login_lat_group radius_login_lat_node radius_login_lat_port radius_login_lat_service radius_login_service radius_login_tcp_port radius_microsoft_ms_acct_auth_type radius_microsoft_ms_acct_eap_type radius_microsoft_ms_arap_challenge radius_microsoft_ms_arap_password_change_reason radius_microsoft_ms_bap_usage radius_microsoft_ms_chap2_pw radius_microsoft_ms_chap2_response radius_microsoft_ms_chap2_success radius_microsoft_ms_chap_challenge radius_microsoft_ms_chap_domain radius_microsoft_ms_chap_error radius_microsoft_ms_chap_lm_enc_pw radius_microsoft_ms_chap_mppe_keys radius_microsoft_ms_chap_nt_enc_pw radius_microsoft_ms_chap_pw_1 radius_microsoft_ms_chap_pw_2 radius_microsoft_ms_chap_response radius_microsoft_ms_filter radius_microsoft_ms_link_drop_time_limit radius_microsoft_ms_link_utilization_threshold radius_microsoft_ms_mppe_encryption_policy radius_microsoft_ms_mppe_encryption_types radius_microsoft_ms_mppe_recv_key radius_microsoft_ms_mppe_send_key radius_microsoft_ms_new_arap_password radius_microsoft_ms_old_arap_password radius_microsoft_ms_primary_dns_server radius_microsoft_ms_primary_nbns_server radius_microsoft_ms_ras_vendor radius_microsoft_ms_ras_version radius_microsoft_ms_secondary_dns_server radius_microsoft_ms_secondary_nbns_server radius_mppe_key_len radius_nas_identifier radius_nas_ip_address radius_nas_port radius_nas_port_type radius_nas_prompt radius_option_salt radius_option_tagged radius_outbound radius_piafs radius_port_limit radius_ppp radius_proxy_state radius_put_addr radius_put_attr radius_put_int radius_put_string radius_put_vendor_addr radius_put_vendor_attr radius_put_vendor_int radius_put_vendor_string radius_reply_message radius_request_authenticator radius_salt_encrypt_attr radius_sdsl radius_send_request radius_server_secret radius_service_type radius_session_timeout radius_slip radius_start radius_state radius_stop radius_strerror radius_sync radius_term_admin_reboot radius_term_admin_reset radius_term_callback radius_term_host_request radius_term_idle_timeout radius_term_lost_carrier radius_term_lost_service radius_term_nas_error radius_term_nas_reboot radius_term_nas_request radius_term_port_error radius_term_port_preempted radius_term_port_suspended radius_term_port_unneeded radius_term_service_unavailable radius_term_session_timeout radius_term_user_error radius_term_user_request radius_termination_action radius_user_name radius_user_password radius_vendor_microsoft radius_vendor_specific radius_virtual radius_wireless_ieee_802_11 radius_wireless_other radius_x_25 radius_x_75 radius_xdsl radius_xylogics radixchar rand random_bytes random_int range rar_host_beos rar_host_msdos rar_host_os2 rar_host_unix rar_host_win32 rar_wrapper_cache_stats rawurldecode rawurlencode read_exif_data readdir readfile readgzfile readline readline_add_history readline_callback_handler_install readline_callback_handler_remove readline_callback_read_char readline_clear_history readline_completion_function readline_info readline_list_history readline_on_new_line readline_read_history readline_redisplay readline_write_history readlink real realpath realpath_cache_get realpath_cache_size register_shutdown_function register_tick_function rename rename_function require require_once reset resource resourcebundle_count resourcebundle_create resourcebundle_get resourcebundle_get_error_code resourcebundle_get_error_message resourcebundle_locales restore_error_handler restore_exception_handler restore_include_path return rewind rewinddir rmdir round rpm_close rpm_get_tag rpm_is_valid rpm_open rpm_version rpmreader_arch rpmreader_archivesize rpmreader_basenames rpmreader_buildarchs rpmreader_buildhost rpmreader_buildtime rpmreader_cachectime rpmreader_cachepkgmtime rpmreader_cachepkgpath rpmreader_cachepkgsize rpmreader_changelogname rpmreader_changelogtext rpmreader_changelogtime rpmreader_classdict rpmreader_conflictflags rpmreader_conflictname rpmreader_conflictversion rpmreader_cookie rpmreader_copyright rpmreader_dependsdict rpmreader_description rpmreader_dirindexes rpmreader_dirnames rpmreader_distribution rpmreader_disturl rpmreader_epoch rpmreader_excludearch rpmreader_excludeos rpmreader_exclusivearch rpmreader_exclusiveos rpmreader_fileclass rpmreader_filecolors rpmreader_filecontexts rpmreader_filedependsn rpmreader_filedependsx rpmreader_filedevices rpmreader_fileflags rpmreader_filegroupname rpmreader_fileinodes rpmreader_filelangs rpmreader_filelinktos rpmreader_filemd5s rpmreader_filemodes rpmreader_filemtimes rpmreader_filerdevs rpmreader_filesizes rpmreader_filestates rpmreader_fileusername rpmreader_fileverifyflags rpmreader_fscontexts rpmreader_gif rpmreader_group rpmreader_icon rpmreader_installcolor rpmreader_installtid rpmreader_installtime rpmreader_instprefixes rpmreader_license rpmreader_maximum rpmreader_minimum rpmreader_name rpmreader_obsoleteflags rpmreader_obsoletename rpmreader_obsoletes rpmreader_obsoleteversion rpmreader_oldfilenames rpmreader_optflags rpmreader_os rpmreader_packager rpmreader_patch rpmreader_patchesflags rpmreader_patchesname rpmreader_patchesversion rpmreader_payloadcompressor rpmreader_payloadflags rpmreader_payloadformat rpmreader_platform rpmreader_policies rpmreader_postin rpmreader_postinprog rpmreader_postun rpmreader_postunprog rpmreader_prefixes rpmreader_prein rpmreader_preinprog rpmreader_preun rpmreader_preunprog rpmreader_provideflags rpmreader_providename rpmreader_provides rpmreader_provideversion rpmreader_recontexts rpmreader_release rpmreader_removetid rpmreader_requireflags rpmreader_requirename rpmreader_requireversion rpmreader_rhnplatform rpmreader_rpmversion rpmreader_serial rpmreader_size rpmreader_source rpmreader_sourcepkgid rpmreader_sourcerpm rpmreader_summary rpmreader_triggerflags rpmreader_triggerindex rpmreader_triggername rpmreader_triggerscriptprog rpmreader_triggerscripts rpmreader_triggerversion rpmreader_url rpmreader_vendor rpmreader_verifyscript rpmreader_verifyscriptprog rpmreader_version rpmreader_xpm rsort rtrim s_all s_executor s_files s_include s_internal s_irgrp s_iroth s_irusr s_irwxg s_irwxo s_irwxu s_iwgrp s_iwoth s_iwusr s_ixgrp s_ixoth s_ixusr s_mail s_memory s_misc s_session s_sql s_vars sa_all sa_messages sa_recent sa_uidnext sa_uidvalidity sa_unseen scandir scandir_sort_ascending scandir_sort_descending scandir_sort_none se_free se_noprefetch se_uid seek_cur seek_end seek_set segv_accerr segv_maperr sem_acquire sem_get sem_release sem_remove serialize session_abort session_cache_expire session_cache_limiter session_commit session_decode session_destroy session_encode session_get_cookie_params session_id session_is_registered session_module_name session_name session_pgsql_add_error session_pgsql_get_error session_pgsql_get_field session_pgsql_reset session_pgsql_set_field session_pgsql_status session_regenerate_id session_register session_register_shutdown session_reset session_save_path session_set_cookie_params session_set_save_handler session_start session_status session_unregister session_unset session_write_close set_error_handler set_exception_handler set_file_buffer set_include_path set_magic_quotes_runtime set_socket_blocking set_time_limit setcookie setlocale setproctitle setrawcookie setthreadtitle settype sha1 sha1_file shell_exec shm_attach shm_detach shm_get_var shm_has_var shm_put_var shm_remove shm_remove_var shmop_close shmop_delete shmop_open shmop_read shmop_size shmop_write show_source shuffle si_asyncio si_kernel si_msggq si_noinfo si_queue si_sigio si_timer si_tkill si_user sid sig_block sig_dfl sig_err sig_ign sig_setmask sig_unblock sigabrt sigalrm sigbaby sigbus sigchld sigcld sigcont sigfpe sighup sigill sigint sigio sigiot sigkill signeurlpaiement sigpipe sigpoll sigprof sigpwr sigquit sigsegv sigstkflt sigstop sigsys sigterm sigtrap sigtstp sigttin sigttou sigurg sigusr1 sigusr2 sigvtalrm sigwinch sigxcpu sigxfsz similar_text simplexml_import_dom simplexml_load_file simplexml_load_string sin sinh sizeof sleep snmp2_get snmp2_getnext snmp2_real_walk snmp2_set snmp2_walk snmp3_get snmp3_getnext snmp3_real_walk snmp3_set snmp3_walk snmp_bit_str snmp_counter snmp_counter64 snmp_get_quick_print snmp_get_valueretrieval snmp_integer snmp_ipaddress snmp_null snmp_object_id snmp_octet_str snmp_oid_output_full snmp_oid_output_module snmp_oid_output_none snmp_oid_output_numeric snmp_oid_output_suffix snmp_oid_output_ucd snmp_opaque snmp_read_mib snmp_set_enum_print snmp_set_oid_numeric_print snmp_set_oid_output_format snmp_set_quick_print snmp_set_valueretrieval snmp_timeticks snmp_uinteger snmp_unsigned snmp_value_library snmp_value_object snmp_value_plain snmpget snmpgetnext snmprealwalk snmpset snmpwalk snmpwalkoid so_bindtodevice so_broadcast so_debug so_dontroute so_error so_free so_keepalive so_linger so_noserver so_oobinline so_rcvbuf so_rcvlowat so_rcvtimeo so_reuseaddr so_reuseport so_sndbuf so_sndlowat so_sndtimeo so_type soap_1_1 soap_1_2 soap_actor_next soap_actor_none soap_actor_unlimatereceiver soap_authentication_basic soap_authentication_digest soap_compression_accept soap_compression_deflate soap_compression_gzip soap_document soap_enc_array soap_enc_object soap_encoded soap_functions_all soap_literal soap_persistence_request soap_persistence_session soap_rpc soap_single_element_arrays soap_ssl_method_sslv2 soap_ssl_method_sslv23
 soap_ssl_method_sslv3 soap_ssl_method_tls soap_use_xsi_array_type soap_wait_one_way_calls sock_dgram sock_raw sock_rdm sock_seqpacket sock_stream socket_accept socket_addrinuse socket_bind socket_clear_error socket_close socket_cmsg_space socket_connect socket_create socket_create_listen socket_create_pair socket_e2big socket_eacces socket_eaddrinuse socket_eaddrnotavail socket_eadv socket_eafnosupport socket_eagain socket_ealready socket_ebade socket_ebadf socket_ebadfd socket_ebadmsg socket_ebadr socket_ebadrqc socket_ebadslt socket_ebusy socket_echrng socket_ecomm socket_econnaborted socket_econnrefused socket_econnreset socket_edestaddrreq socket_ediscon socket_edquot socket_eduot socket_eexist socket_efault socket_ehostdown socket_ehostunreach socket_eidrm socket_einprogress socket_eintr socket_einval socket_eio socket_eisconn socket_eisdir socket_eisnam socket_el2hlt socket_el2nsync socket_el3hlt socket_el3rst socket_elnrng socket_eloop socket_emediumtype socket_emfile socket_emlink socket_emsgsize socket_emultihop socket_enametoolong socket_enetdown socket_enetreset socket_enetunreach socket_enfile socket_enoano socket_enobufs socket_enocsi socket_enodata socket_enodev socket_enoent socket_enolck socket_enolink socket_enomedium socket_enomem socket_enomsg socket_enonet socket_enoprotoopt socket_enospc socket_enosr socket_enostr socket_enosys socket_enotblk socket_enotconn socket_enotdir socket_enotempty socket_enotsock socket_enotty socket_enotuniq socket_enxio socket_eopnotsupp socket_eperm socket_epfnosupport socket_epipe socket_eproclim socket_eproto socket_eprotonosupport socket_eprotoopt socket_eprototype socket_eremchg socket_eremote socket_eremoteio socket_erestart socket_erofs socket_eshutdown socket_esocktnosupport socket_espipe socket_esrmnt socket_estale socket_estrpipe socket_etime socket_etimedout socket_etoomanyrefs socket_etoomyrefs socket_eunatch socket_eusers socket_ewouldblock socket_exdev socket_exfull socket_get_option socket_get_status socket_getopt socket_getpeername socket_getsockname socket_host_not_found socket_import_stream socket_last_error socket_listen socket_no_address socket_no_data socket_no_recovery socket_notinitialised socket_read socket_recv socket_recvfrom socket_recvmsg socket_select socket_send socket_sendmsg socket_sendto socket_set_block socket_set_blocking socket_set_nonblock socket_set_option socket_set_timeout socket_setopt socket_shutdown socket_strerror socket_sysnotready socket_try_again socket_vernotsupported socket_write sol_socket sol_tcp sol_udp somaxconn sort sort_asc sort_desc sort_flag_case sort_locale_string sort_natural sort_numeric sort_regular sort_string sortarrival sortcc sortdate sortfrom sortsize sortsubject sortto soundex spl_autoload spl_autoload_call spl_autoload_extensions spl_autoload_functions spl_autoload_register spl_autoload_unregister spl_classes spl_object_hash split spliti sprintf sql_best_rowid sql_bigint sql_binary sql_bit sql_char sql_concur_lock sql_concur_read_only sql_concur_rowver sql_concur_values sql_concurrency sql_cur_use_driver sql_cur_use_if_needed sql_cur_use_odbc sql_cursor_dynamic sql_cursor_forward_only sql_cursor_keyset_driven sql_cursor_static sql_cursor_type sql_date sql_decimal sql_double sql_ensure sql_fetch_first sql_fetch_next sql_float sql_index_all sql_index_unique sql_integer sql_keyset_size sql_longvarbinary sql_longvarchar sql_no_nulls sql_nullable sql_numeric sql_odbc_cursors sql_quick sql_real sql_regcase sql_rowver sql_scope_currow sql_scope_session sql_scope_transaction sql_smallint sql_time sql_timestamp sql_tinyint sql_type_date sql_type_time sql_type_timestamp sql_varbinary sql_varchar sql_wchar sql_wlongvarchar sql_wvarchar sqlbit sqlchar sqlflt4 sqlflt8 sqlint1 sqlint2 sqlint4 sqlite3_assoc sqlite3_blob sqlite3_both sqlite3_float sqlite3_integer sqlite3_null sqlite3_num sqlite3_open_create sqlite3_open_readonly sqlite3_open_readwrite sqlite3_text sqlite_abort sqlite_array_query sqlite_assoc sqlite_auth sqlite_both sqlite_busy sqlite_busy_timeout sqlite_cantopen sqlite_changes sqlite_close sqlite_column sqlite_constraint sqlite_corrupt sqlite_create_aggregate sqlite_create_function sqlite_current sqlite_done sqlite_empty sqlite_error sqlite_error_string sqlite_escape_string sqlite_exec sqlite_factory sqlite_fetch_all sqlite_fetch_array sqlite_fetch_column_types sqlite_fetch_object sqlite_fetch_single sqlite_fetch_string sqlite_field_name sqlite_format sqlite_full sqlite_has_more sqlite_has_prev sqlite_internal sqlite_interrupt sqlite_ioerr sqlite_key sqlite_last_error sqlite_last_insert_rowid sqlite_libencoding sqlite_libversion sqlite_locked sqlite_mismatch sqlite_misuse sqlite_next sqlite_nolfs sqlite_nomem sqlite_notadb sqlite_notfound sqlite_num sqlite_num_fields sqlite_num_rows sqlite_ok sqlite_open sqlite_perm sqlite_popen sqlite_prev sqlite_protocol sqlite_query sqlite_readonly sqlite_rewind sqlite_row sqlite_schema sqlite_seek sqlite_single_query sqlite_toobig sqlite_udf_decode_binary sqlite_udf_encode_binary sqlite_unbuffered_query sqlite_valid sqlsrv_begin_transaction sqlsrv_cancel sqlsrv_client_info sqlsrv_close sqlsrv_commit sqlsrv_configure sqlsrv_connect sqlsrv_cursor_buffered sqlsrv_cursor_dynamic sqlsrv_cursor_forward sqlsrv_cursor_keyset sqlsrv_cursor_static sqlsrv_enc_binary sqlsrv_enc_char sqlsrv_err_all sqlsrv_err_errors sqlsrv_err_warnings sqlsrv_errors sqlsrv_execute sqlsrv_fetch sqlsrv_fetch_array sqlsrv_fetch_assoc sqlsrv_fetch_both sqlsrv_fetch_numeric sqlsrv_fetch_object sqlsrv_field_metadata sqlsrv_free_stmt sqlsrv_get_config sqlsrv_get_field sqlsrv_has_rows sqlsrv_log_severity_all sqlsrv_log_severity_error sqlsrv_log_severity_notice sqlsrv_log_severity_warning sqlsrv_log_system_all sqlsrv_log_system_conn sqlsrv_log_system_init sqlsrv_log_system_off sqlsrv_log_system_stmt sqlsrv_log_system_util sqlsrv_next_result sqlsrv_nullable_no sqlsrv_nullable_unknown sqlsrv_nullable_yes sqlsrv_num_fields sqlsrv_num_rows sqlsrv_param_in sqlsrv_param_inout sqlsrv_param_out sqlsrv_phptype_datetime sqlsrv_phptype_float sqlsrv_phptype_int sqlsrv_phptype_null sqlsrv_phptype_stream sqlsrv_phptype_string sqlsrv_prepare sqlsrv_query sqlsrv_rollback sqlsrv_rows_affected sqlsrv_scroll_absolute sqlsrv_scroll_first sqlsrv_scroll_last sqlsrv_scroll_next sqlsrv_scroll_prior sqlsrv_scroll_relative sqlsrv_send_stream_data sqlsrv_server_info sqlsrv_sqltype_bigint sqlsrv_sqltype_binary sqlsrv_sqltype_bit sqlsrv_sqltype_char sqlsrv_sqltype_date sqlsrv_sqltype_datetime sqlsrv_sqltype_datetime2 sqlsrv_sqltype_datetimeoffset sqlsrv_sqltype_decimal sqlsrv_sqltype_float sqlsrv_sqltype_image sqlsrv_sqltype_int sqlsrv_sqltype_money sqlsrv_sqltype_nchar sqlsrv_sqltype_ntext sqlsrv_sqltype_numeric sqlsrv_sqltype_nvarchar sqlsrv_sqltype_real sqlsrv_sqltype_smalldatetime sqlsrv_sqltype_smallint sqlsrv_sqltype_smallmoney sqlsrv_sqltype_text sqlsrv_sqltype_time sqlsrv_sqltype_timestamp sqlsrv_sqltype_tinyint sqlsrv_sqltype_udt sqlsrv_sqltype_uniqueidentifier sqlsrv_sqltype_varbinary sqlsrv_sqltype_varchar sqlsrv_sqltype_xml sqlsrv_txn_read_committed sqlsrv_txn_read_serializable sqlsrv_txn_read_uncommitted sqlsrv_txn_repeatable_read sqlsrv_txn_serializable sqlsrv_txn_snapshot sqlt_afc sqlt_avc sqlt_bdouble sqlt_bfilee sqlt_bfloat sqlt_bin sqlt_blob sqlt_bol sqlt_cfilee sqlt_chr sqlt_clob sqlt_flt sqlt_int sqlt_lbi sqlt_lng sqlt_lvc sqlt_nty sqlt_num sqlt_odt sqlt_rdd sqlt_rset sqlt_str sqlt_uin sqlt_vcs sqltext sqlvarchar sqrt srand sscanf ssdeep_fuzzy_compare ssdeep_fuzzy_hash ssdeep_fuzzy_hash_filename ssh2_auth_agent ssh2_auth_hostbased_file ssh2_auth_none ssh2_auth_password ssh2_auth_pubkey_file ssh2_connect ssh2_default_term_height ssh2_default_term_unit ssh2_default_term_width ssh2_default_terminal ssh2_exec ssh2_fetch_stream ssh2_fingerprint ssh2_fingerprint_hex ssh2_fingerprint_md5 ssh2_fingerprint_raw ssh2_fingerprint_sha1 ssh2_methods_negotiated ssh2_publickey_add ssh2_publickey_init ssh2_publickey_list ssh2_publickey_remove ssh2_scp_recv ssh2_scp_send ssh2_sftp ssh2_sftp_chmod ssh2_sftp_lstat ssh2_sftp_mkdir ssh2_sftp_readlink ssh2_sftp_realpath ssh2_sftp_rename ssh2_sftp_rmdir ssh2_sftp_stat ssh2_sftp_symlink ssh2_sftp_unlink ssh2_shell ssh2_stream_stderr ssh2_stream_stdio ssh2_term_unit_chars ssh2_term_unit_pixels ssh2_tunnel st_set st_silent st_uid stat statement_trace static stats_absolute_deviation stats_cdf_beta stats_cdf_binomial stats_cdf_cauchy stats_cdf_chisquare stats_cdf_exponential stats_cdf_f stats_cdf_gamma stats_cdf_laplace stats_cdf_logistic stats_cdf_negative_binomial stats_cdf_noncentral_chisquare stats_cdf_noncentral_f stats_cdf_poisson stats_cdf_t stats_cdf_uniform stats_cdf_weibull stats_covariance stats_den_uniform stats_dens_beta stats_dens_cauchy stats_dens_chisquare stats_dens_exponential stats_dens_f stats_dens_gamma stats_dens_laplace stats_dens_logistic stats_dens_negative_binomial stats_dens_normal stats_dens_pmf_binomial stats_dens_pmf_hypergeometric stats_dens_pmf_poisson stats_dens_t stats_dens_weibull stats_harmonic_mean stats_kurtosis stats_rand_gen_beta stats_rand_gen_chisquare stats_rand_gen_exponential stats_rand_gen_f stats_rand_gen_funiform stats_rand_gen_gamma stats_rand_gen_ibinomial stats_rand_gen_ibinomial_negative stats_rand_gen_int stats_rand_gen_ipoisson stats_rand_gen_iuniform stats_rand_gen_noncenral_chisquare stats_rand_gen_noncentral_f stats_rand_gen_noncentral_t stats_rand_gen_normal stats_rand_gen_t stats_rand_get_seeds stats_rand_phrase_to_seeds stats_rand_ranf stats_rand_setall stats_skew stats_standard_deviation stats_stat_binomial_coef stats_stat_correlation stats_stat_gennch stats_stat_independent_t stats_stat_innerproduct stats_stat_noncentral_t stats_stat_paired_t stats_stat_percentile stats_stat_powersum stats_variance stdclass str_getcsv
 str_ireplace str_pad str_pad_both str_pad_left str_pad_right str_repeat str_replace str_rot13 str_shuffle str_split str_word_count strcasecmp strchr strcmp strcoll strcspn stream_bucket_append stream_bucket_make_writeable stream_bucket_new stream_bucket_prepend stream_buffer_full stream_buffer_line stream_buffer_none stream_cast_as_stream stream_cast_for_select stream_client_async_connect stream_client_connect stream_client_persistent stream_context_create stream_context_get_default stream_context_get_options stream_context_get_params stream_context_set_default stream_context_set_option stream_context_set_params stream_copy_to_stream stream_crypto_method_any_client stream_crypto_method_any_server stream_crypto_method_sslv23_client stream_crypto_method_sslv23_server stream_crypto_method_sslv2_client stream_crypto_method_sslv2_server stream_crypto_method_sslv3_client stream_crypto_method_sslv3_server stream_crypto_method_tls_client stream_crypto_method_tls_server stream_crypto_method_tlsv1_0_client stream_crypto_method_tlsv1_0_server stream_crypto_method_tlsv1_1_client stream_crypto_method_tlsv1_1_server stream_crypto_method_tlsv1_2_client stream_crypto_method_tlsv1_2_server stream_encoding stream_enforce_safe_mode stream_filter_all stream_filter_append stream_filter_prepend stream_filter_read stream_filter_register stream_filter_remove stream_filter_write stream_get_contents stream_get_filters stream_get_line stream_get_meta_data stream_get_transports stream_get_wrappers stream_ignore_url stream_ipproto_icmp stream_ipproto_ip stream_ipproto_raw stream_ipproto_tcp stream_ipproto_udp stream_is_local stream_is_url stream_meta_access stream_meta_group stream_meta_group_name stream_meta_owner stream_meta_owner_name stream_meta_touch stream_mkdir_recursive stream_must_seek stream_notification_callback stream_notify_auth_required stream_notify_auth_result stream_notify_completed stream_notify_connect stream_notify_failure stream_notify_file_size_is stream_notify_mime_type_is stream_notify_progress stream_notify_redirected stream_notify_resolve stream_notify_severity_err stream_notify_severity_info stream_notify_severity_warn stream_oob stream_option_blocking stream_option_read_buffer stream_option_read_timeout stream_option_write_buffer stream_peek stream_pf_inet stream_pf_inet6 stream_pf_unix stream_register_wrapper stream_report_errors stream_resolve_include_path stream_select stream_server_bind stream_server_listen stream_set_blocking stream_set_chunk_size stream_set_read_buffer stream_set_timeout stream_set_write_buffer stream_shut_rd stream_shut_rdwr stream_shut_wr stream_sock_dgram stream_sock_raw stream_sock_rdm stream_sock_seqpacket stream_sock_stream stream_socket_accept stream_socket_client stream_socket_enable_crypto stream_socket_get_name stream_socket_pair stream_socket_recvfrom stream_socket_sendto stream_socket_server stream_socket_shutdown stream_supports_lock stream_url_stat_link stream_url_stat_quiet stream_use_path stream_wrapper_register stream_wrapper_restore stream_wrapper_unregister strftime string strip_tags stripcslashes stripos stripslashes stristr strlen strnatcasecmp strnatcmp strncasecmp strncmp strpbrk strpos strptime strrchr strrev strripos strrpos strspn strstr strtok strtolower strtotime strtoupper strtr strval substr substr_compare substr_count substr_replace suhosin_patch suhosin_patch_version summary_trace sunfuncs_ret_double sunfuncs_ret_string sunfuncs_ret_timestamp svn_add svn_auth_get_parameter svn_auth_param_config svn_auth_param_config_dir svn_auth_param_default_password svn_auth_param_default_username svn_auth_param_dont_store_passwords svn_auth_param_no_auth_cache svn_auth_param_non_interactive svn_auth_param_server_group svn_auth_param_ssl_server_cert_info svn_auth_param_ssl_server_failures svn_auth_set_parameter svn_blame svn_cat svn_checkout svn_cleanup svn_client_version svn_commit svn_delete svn_diff svn_export svn_fs_abort_txn svn_fs_apply_text svn_fs_begin_txn2 svn_fs_change_node_prop svn_fs_check_path svn_fs_config_fs_type svn_fs_contents_changed svn_fs_copy svn_fs_delete svn_fs_dir_entries svn_fs_file_contents svn_fs_file_length svn_fs_is_dir svn_fs_is_file svn_fs_make_dir svn_fs_make_file svn_fs_node_created_rev svn_fs_node_prop svn_fs_props_changed svn_fs_revision_prop svn_fs_revision_root svn_fs_txn_root svn_fs_type_bdb svn_fs_type_fsfs svn_fs_youngest_rev svn_import svn_log svn_ls svn_mkdir svn_node_dir svn_node_file svn_node_none svn_node_unknown svn_prop_revision_author svn_prop_revision_date svn_prop_revision_log svn_prop_revision_orig_date svn_repos_create svn_repos_fs svn_repos_fs_begin_txn_for_commit svn_repos_fs_commit_txn svn_repos_hotcopy svn_repos_open svn_repos_recover svn_revert svn_revision_head svn_status svn_update svn_wc_status_added svn_wc_status_conflicted svn_wc_status_deleted svn_wc_status_external svn_wc_status_ignored svn_wc_status_incomplete svn_wc_status_merged svn_wc_status_missing svn_wc_status_modified svn_wc_status_none svn_wc_status_normal svn_wc_status_obstructed svn_wc_status_replaced svn_wc_status_unversioned swfaction_data swfaction_enterframe swfaction_keydown swfaction_keyup swfaction_mousedown swfaction_mousemove swfaction_mouseup swfaction_onload swfaction_unload swfbutton_down swfbutton_dragout swfbutton_dragover swfbutton_hit swfbutton_mousedown swfbutton_mouseout swfbutton_mouseover swfbutton_mouseup swfbutton_mouseupoutside swfbutton_over swfbutton_up swffill_clipped_bitmap swffill_linear_gradient swffill_radial_gradient swffill_tiled_bitmap swftextfield_align_center swftextfield_align_justify swftextfield_align_left swftextfield_align_right swftextfield_drawbox swftextfield_haslength swftextfield_html swftextfield_multiline swftextfield_noedit swftextfield_noselect swftextfield_password swftextfield_wordwrap switch sybase_affected_rows sybase_close sybase_connect sybase_data_seek sybase_deadlock_retry_count sybase_fetch_array sybase_fetch_assoc sybase_fetch_field sybase_fetch_object sybase_fetch_row sybase_field_seek sybase_free_result sybase_get_last_message sybase_min_client_severity sybase_min_error_severity sybase_min_message_severity sybase_min_server_severity sybase_num_fields sybase_num_rows sybase_pconnect sybase_query sybase_result sybase_select_db sybase_set_message_handler sybase_unbuffered_query symlink sys_get_temp_dir sys_getloadavg syslog system t_abstract t_and_equal t_array t_array_cast t_as t_bad_character t_bool_cast t_boolean_and t_boolean_or t_break t_callable t_case t_catch t_character t_class t_class_c t_clone t_close_tag t_comment t_concat_equal t_const t_constant_encapsed_string t_continue t_curly_open t_dec t_declare t_default t_dir t_div_equal t_dnumber t_do t_doc_comment t_dollar_open_curly_braces t_double_arrow t_double_cast t_double_colon t_echo t_ellipsis t_else t_elseif t_empty t_encapsed_and_whitespace t_end_heredoc t_enddeclare t_endfor t_endforeach t_endif t_endswitch t_endwhile t_eval t_exit t_extends t_file t_final t_finally t_fmt t_fmt_ampm t_for t_foreach t_func_c t_function t_global t_goto t_halt_compiler t_if t_implements t_inc t_include t_include_once t_inline_html t_instanceof t_insteadof t_int_cast t_interface t_is_equal t_is_greater_or_equal t_is_identical t_is_not_equal t_is_not_identical t_is_smaller_or_equal t_isset t_line t_list t_lnumber t_logical_and t_logical_or t_logical_xor t_method_c t_minus_equal t_mod_equal t_mul_equal t_namespace t_new t_ns_c t_ns_separator t_num_string t_object_cast t_object_operator t_open_tag t_open_tag_with_echo t_or_equal t_paamayim_nekudotayim t_plus_equal t_pow t_pow_equal t_print t_private t_protected t_public t_require t_require_once t_return t_sl t_sl_equal t_sr t_sr_equal t_start_heredoc t_static t_string t_string_cast t_string_varname t_switch t_throw t_trait t_trait_c t_try t_unset t_unset_cast t_use t_var t_variable t_while t_whitespace t_xor_equal t_yield taint tan tanh tcp_nodelay tcpwrap_check tempnam textdomain thousands_sep thousep throw tidy_access_count tidy_clean_repair tidy_config_count tidy_diagnose tidy_error_count tidy_get_body tidy_get_config tidy_get_error_buffer tidy_get_head tidy_get_html tidy_get_html_ver tidy_get_output tidy_get_release tidy_get_root tidy_get_status tidy_getopt tidy_is_xhtml tidy_is_xml tidy_load_config tidy_nodetype_asp tidy_nodetype_cdata tidy_nodetype_comment tidy_nodetype_doctype tidy_nodetype_end tidy_nodetype_jste tidy_nodetype_php tidy_nodetype_procins tidy_nodetype_root tidy_nodetype_section tidy_nodetype_start tidy_nodetype_startend tidy_nodetype_text tidy_nodetype_xmldecl tidy_parse_file tidy_parse_string tidy_repair_file tidy_repair_string tidy_reset_config tidy_save_config tidy_set_encoding tidy_setopt tidy_tag_a tidy_tag_abbr tidy_tag_acronym tidy_tag_address tidy_tag_align tidy_tag_applet tidy_tag_area tidy_tag_b tidy_tag_base tidy_tag_basefont tidy_tag_bdo tidy_tag_bgsound tidy_tag_big tidy_tag_blink tidy_tag_blockquote tidy_tag_body tidy_tag_br tidy_tag_button tidy_tag_caption tidy_tag_center tidy_tag_cite tidy_tag_code tidy_tag_col tidy_tag_colgroup tidy_tag_comment tidy_tag_dd tidy_tag_del tidy_tag_dfn tidy_tag_dir tidy_tag_div tidy_tag_dl tidy_tag_dt tidy_tag_em tidy_tag_embed tidy_tag_fieldset tidy_tag_font tidy_tag_form tidy_tag_frame tidy_tag_frameset tidy_tag_h1 tidy_tag_h2 tidy_tag_h3 tidy_tag_h4 tidy_tag_h5 tidy_tag_h6 tidy_tag_head tidy_tag_hr tidy_tag_html tidy_tag_i tidy_tag_iframe tidy_tag_ilayer tidy_tag_img tidy_tag_input tidy_tag_ins tidy_tag_isindex tidy_tag_kbd tidy_tag_keygen tidy_tag_label tidy_tag_layer tidy_tag_legend tidy_tag_li tidy_tag_link tidy_tag_listing tidy_tag_map tidy_tag_marquee tidy_tag_menu tidy_tag_meta tidy_tag_multicol tidy_tag_nobr tidy_tag_noembed tidy_tag_noframes tidy_tag_nolayer tidy_tag_nosave tidy_tag_noscript tidy_tag_object tidy_tag_ol
 tidy_tag_optgroup tidy_tag_option tidy_tag_p tidy_tag_param tidy_tag_plaintext tidy_tag_pre tidy_tag_q tidy_tag_rb tidy_tag_rbc tidy_tag_rp tidy_tag_rt tidy_tag_rtc tidy_tag_ruby tidy_tag_s tidy_tag_samp tidy_tag_script tidy_tag_select tidy_tag_server tidy_tag_servlet tidy_tag_small tidy_tag_spacer tidy_tag_span tidy_tag_strike tidy_tag_strong tidy_tag_style tidy_tag_sub tidy_tag_sup tidy_tag_table tidy_tag_tbody tidy_tag_td tidy_tag_textarea tidy_tag_tfoot tidy_tag_th tidy_tag_thead tidy_tag_title tidy_tag_tr tidy_tag_tt tidy_tag_u tidy_tag_ul tidy_tag_unknown tidy_tag_var tidy_tag_wbr tidy_tag_xmp tidy_warning_count time time_nanosleep time_sleep_until timezone_abbreviations_list timezone_identifiers_list timezone_location_get timezone_name_from_abbr timezone_name_get timezone_offset_get timezone_open timezone_transitions_get timezone_version_get timing_trace tmpfile token_get_all token_name touch trader_acos trader_ad trader_add trader_adosc trader_adx trader_adxr trader_apo trader_aroon trader_aroonosc trader_asin trader_atan trader_atr trader_avgprice trader_bbands trader_beta trader_bop trader_cci trader_cdl2crows trader_cdl3blackcrows trader_cdl3inside trader_cdl3linestrike trader_cdl3outside trader_cdl3starsinsouth trader_cdl3whitesoldiers trader_cdlabandonedbaby trader_cdladvanceblock trader_cdlbelthold trader_cdlbreakaway trader_cdlclosingmarubozu trader_cdlconcealbabyswall trader_cdlcounterattack trader_cdldarkcloudcover trader_cdldoji trader_cdldojistar trader_cdldragonflydoji trader_cdlengulfing trader_cdleveningdojistar trader_cdleveningstar trader_cdlgapsidesidewhite trader_cdlgravestonedoji trader_cdlhammer trader_cdlhangingman trader_cdlharami trader_cdlharamicross trader_cdlhighwave trader_cdlhikkake trader_cdlhikkakemod trader_cdlhomingpigeon trader_cdlidentical3crows trader_cdlinneck trader_cdlinvertedhammer trader_cdlkicking trader_cdlkickingbylength trader_cdlladderbottom trader_cdllongleggeddoji trader_cdllongline trader_cdlmarubozu trader_cdlmatchinglow trader_cdlmathold trader_cdlmorningdojistar trader_cdlmorningstar trader_cdlonneck trader_cdlpiercing trader_cdlrickshawman trader_cdlrisefall3methods trader_cdlseparatinglines trader_cdlshootingstar trader_cdlshortline trader_cdlspinningtop trader_cdlstalledpattern trader_cdlsticksandwich trader_cdltakuri trader_cdltasukigap trader_cdlthrusting trader_cdltristar trader_cdlunique3river trader_cdlupsidegap2crows trader_cdlxsidegap3methods trader_ceil trader_cmo trader_compatibility_default trader_compatibility_metastock trader_correl trader_cos trader_cosh trader_dema trader_div trader_dx trader_ema trader_err_alloc_err trader_err_bad_object trader_err_bad_param trader_err_func_not_found trader_err_group_not_found trader_err_input_not_all_initialize trader_err_internal_error trader_err_invalid_handle trader_err_invalid_list_type trader_err_invalid_param_function trader_err_invalid_param_holder trader_err_invalid_param_holder_type trader_err_lib_not_initialize trader_err_not_supported trader_err_out_of_range_end_index trader_err_out_of_range_start_index trader_err_output_not_all_initialize trader_err_success trader_err_unknown_error trader_errno trader_exp trader_floor trader_func_unst_adx trader_func_unst_adxr trader_func_unst_all trader_func_unst_atr trader_func_unst_cmo trader_func_unst_dx trader_func_unst_ema trader_func_unst_ht_dcperiod trader_func_unst_ht_dcphase trader_func_unst_ht_phasor trader_func_unst_ht_sine trader_func_unst_ht_trendline trader_func_unst_ht_trendmode trader_func_unst_kama trader_func_unst_mama trader_func_unst_mfi trader_func_unst_minus_di trader_func_unst_minus_dm trader_func_unst_natr trader_func_unst_none trader_func_unst_plus_di trader_func_unst_plus_dm trader_func_unst_rsi trader_func_unst_stochrsi trader_func_unst_t3 trader_get_compat trader_get_unstable_period trader_ht_dcperiod trader_ht_dcphase trader_ht_phasor trader_ht_sine trader_ht_trendline trader_ht_trendmode trader_kama trader_linearreg trader_linearreg_angle trader_linearreg_intercept trader_linearreg_slope trader_ln trader_log10 trader_ma trader_ma_type_dema trader_ma_type_ema trader_ma_type_kama trader_ma_type_mama trader_ma_type_sma trader_ma_type_t3 trader_ma_type_tema trader_ma_type_trima trader_ma_type_wma trader_macd trader_macdext trader_macdfix trader_mama trader_mavp trader_max trader_maxindex trader_medprice trader_mfi trader_midpoint trader_midprice trader_min trader_minindex trader_minmax trader_minmaxindex trader_minus_di trader_minus_dm trader_mom trader_mult trader_natr trader_obv trader_plus_di trader_plus_dm trader_ppo trader_real_max trader_real_min trader_roc trader_rocp trader_rocr trader_rocr100 trader_rsi trader_sar trader_sarext trader_set_compat trader_set_unstable_period trader_sin trader_sinh trader_sma trader_sqrt trader_stddev trader_stoch trader_stochf trader_stochrsi trader_sub trader_sum trader_t3 trader_tan trader_tanh trader_tema trader_trange trader_trima trader_trix trader_tsf trader_typprice trader_ultosc trader_var trader_wclprice trader_willr trader_wma trait trait_exists tran_commit_class_commit_instance tran_commit_class_uncommit_instance tran_rep_class_commit_instance tran_rep_class_rep_instance tran_rep_class_uncommit_instance tran_serializable transliterator_create transliterator_create_from_rules transliterator_create_inverse transliterator_get_error_code transliterator_get_error_message transliterator_list_ids transliterator_transliterate trap_brkpt trap_trace trigger_error trim true try typeapplication typeaudio typeimage typemessage typemodel typemultipart typeother typetext typevideo u_ambiguous_alias_warning u_bad_variable_definition u_brk_assign_error u_brk_error_limit u_brk_error_start u_brk_hex_digits_expected u_brk_init_error u_brk_internal_error u_brk_malformed_rule_tag u_brk_mismatched_paren u_brk_new_line_in_quoted_string u_brk_rule_empty_set u_brk_rule_syntax u_brk_semicolon_expected u_brk_unclosed_set u_brk_undefined_variable u_brk_unrecognized_option u_brk_variable_redfinition u_buffer_overflow_error u_ce_not_found_error u_collator_version_mismatch u_different_uca_version u_enum_out_of_sync_error u_error_limit u_error_warning_limit u_error_warning_start u_file_access_error u_fmt_parse_error_limit u_fmt_parse_error_start u_idna_ace_prefix_error u_idna_check_bidi_error u_idna_domain_name_too_long_error u_idna_error_limit u_idna_error_start u_idna_label_too_long_error u_idna_prohibited_error u_idna_std3_ascii_rules_error u_idna_unassigned_error u_idna_verification_error u_idna_zero_length_label_error u_illegal_argument_error u_illegal_char_found u_illegal_char_in_segment u_illegal_character u_illegal_escape_sequence u_illegal_pad_position u_index_outofbounds_error u_internal_program_error u_internal_transliterator_error u_invalid_char_found u_invalid_format_error u_invalid_function u_invalid_id u_invalid_property_pattern u_invalid_rbt_syntax u_invalid_state_error u_invalid_table_file u_invalid_table_format u_invariant_conversion_error u_malformed_exponential_pattern u_malformed_pragma u_malformed_rule u_malformed_set u_malformed_symbol_reference u_malformed_unicode_escape u_malformed_variable_definition u_malformed_variable_reference u_memory_allocation_error u_message_parse_error u_mismatched_segment_delimiters u_misplaced_anchor_start u_misplaced_compound_filter u_misplaced_cursor_offset u_misplaced_quantifier u_missing_operator u_missing_resource_error u_missing_segment_close u_multiple_ante_contexts u_multiple_compound_filters u_multiple_cursors u_multiple_decimal_separators u_multiple_decimal_seperators u_multiple_exponential_symbols u_multiple_pad_specifiers u_multiple_percent_symbols u_multiple_permill_symbols u_multiple_post_contexts u_no_space_available u_no_write_permission u_parse_error u_parse_error_limit u_parse_error_start u_pattern_syntax_error u_primary_too_long_error u_regex_bad_escape_sequence u_regex_bad_interval u_regex_error_limit u_regex_error_start u_regex_internal_error u_regex_invalid_back_ref u_regex_invalid_flag u_regex_invalid_state u_regex_look_behind_limit u_regex_max_lt_min u_regex_mismatched_paren u_regex_number_too_big u_regex_property_syntax u_regex_rule_syntax u_regex_set_contains_string u_regex_unimplemented u_resource_type_mismatch u_rule_mask_error u_safeclone_allocated_warning u_sort_key_too_short_warning u_standard_error_limit u_state_old_warning u_state_too_old_error u_string_not_terminated_warning u_stringprep_check_bidi_error u_stringprep_prohibited_error u_stringprep_unassigned_error u_too_many_aliases_error u_trailing_backslash u_truncated_char_found u_unclosed_segment u_undefined_segment_reference u_undefined_variable u_unexpected_token u_unmatched_braces u_unquoted_special u_unsupported_attribute u_unsupported_error u_unsupported_escape_sequence u_unsupported_property u_unterminated_quote u_useless_collator_error u_using_default_warning u_using_fallback_warning u_variable_range_exhausted u_variable_range_overlap u_zero_error uasort ucfirst ucwords udm_add_search_limit udm_alloc_agent udm_alloc_agent_array udm_api_version udm_cat_list udm_cat_path udm_check_charset udm_clear_search_limits udm_crc32 udm_errno udm_error udm_find udm_free_agent udm_free_ispell_data udm_free_res udm_get_doc_count udm_get_res_field udm_get_res_param udm_hash32 udm_load_ispell_data udm_set_agent_param uksort uloc_actual_locale uloc_valid_locale umask uniqid unixtojd unknown_type unlink unpack unregister_tick_function unserialize unset untaint upload_err_cant_write upload_err_extension upload_err_form_size upload_err_ini_size upload_err_no_file upload_err_no_tmp_dir upload_err_ok upload_err_partial urldecode urlencode use use_soap_error_handler user_error usleep usort utf8_decode utf8_encode var var_dump var_export varcmp_eq varcmp_gt varcmp_lt varcmp_null variant_abs
 variant_add variant_and variant_cast variant_cat variant_cmp variant_date_from_timestamp variant_date_to_timestamp variant_div variant_eqv variant_fix variant_get_type variant_idiv variant_imp variant_int variant_mod variant_mul variant_neg variant_not variant_or variant_pow variant_round variant_set variant_set_type variant_sub variant_xor version_compare vfprintf virtual void vpopmail_add_alias_domain vpopmail_add_alias_domain_ex vpopmail_add_domain vpopmail_add_domain_ex vpopmail_add_user vpopmail_alias_add vpopmail_alias_del vpopmail_alias_del_domain vpopmail_alias_get vpopmail_alias_get_all vpopmail_auth_user vpopmail_del_domain vpopmail_del_domain_ex vpopmail_del_user vpopmail_error vpopmail_passwd vpopmail_set_user_quota vprintf vsprintf vt_array vt_bool vt_bstr vt_byref vt_cy vt_date vt_decimal vt_dispatch vt_empty vt_error vt_i1 vt_i2 vt_i4 vt_int vt_null vt_r4 vt_r8 vt_ui1 vt_ui2 vt_ui4 vt_uint vt_unknown vt_variant wddx_add_vars wddx_deserialize wddx_packet_end wddx_packet_start wddx_serialize_value wddx_serialize_vars while win32_above_normal_priority_class win32_below_normal_priority_class win32_continue_service win32_create_service win32_delete_service win32_error_access_denied win32_error_circular_dependency win32_error_database_does_not_exist win32_error_dependent_services_running win32_error_duplicate_service_name win32_error_failed_service_controller_connect win32_error_insufficient_buffer win32_error_invalid_data win32_error_invalid_handle win32_error_invalid_level win32_error_invalid_name win32_error_invalid_parameter win32_error_invalid_service_account win32_error_invalid_service_control win32_error_path_not_found win32_error_service_already_running win32_error_service_cannot_accept_ctrl win32_error_service_database_locked win32_error_service_dependency_deleted win32_error_service_dependency_fail win32_error_service_disabled win32_error_service_does_not_exist win32_error_service_exists win32_error_service_logon_failed win32_error_service_marked_for_delete win32_error_service_no_thread win32_error_service_not_active win32_error_service_request_timeout win32_error_shutdown_in_progress win32_get_last_control_message win32_high_priority_class win32_idle_priority_class win32_no_error win32_normal_priority_class win32_pause_service win32_ps_list_procs win32_ps_stat_mem win32_ps_stat_proc win32_query_service_status win32_realtime_priority_class win32_service_accept_pause_continue win32_service_accept_preshutdown win32_service_accept_shutdown win32_service_accept_stop win32_service_auto_start win32_service_continue_pending win32_service_control_continue win32_service_control_interrogate win32_service_control_pause win32_service_control_preshutdown win32_service_control_shutdown win32_service_control_stop win32_service_demand_start win32_service_disabled win32_service_error_ignore win32_service_error_normal win32_service_interactive_process win32_service_pause_pending win32_service_paused win32_service_running win32_service_runs_in_system_process win32_service_start_pending win32_service_stop_pending win32_service_stopped win32_service_win32_own_process win32_service_win32_own_process_interactive win32_set_service_status win32_start_service win32_start_service_ctrl_dispatcher win32_stop_service wincache_fcache_fileinfo wincache_fcache_meminfo wincache_lock wincache_ocache_fileinfo wincache_ocache_meminfo wincache_refresh_if_changed wincache_rplist_fileinfo wincache_rplist_meminfo wincache_scache_info wincache_scache_meminfo wincache_ucache_add wincache_ucache_cas wincache_ucache_clear wincache_ucache_dec wincache_ucache_delete wincache_ucache_exists wincache_ucache_get wincache_ucache_inc wincache_ucache_info wincache_ucache_meminfo wincache_ucache_set wincache_unlock wnohang wordwrap wsdl_cache_both wsdl_cache_disk wsdl_cache_memory wsdl_cache_none wuntraced x509_purpose_any x509_purpose_crl_sign x509_purpose_ns_ssl_server x509_purpose_smime_encrypt x509_purpose_smime_sign x509_purpose_ssl_client x509_purpose_ssl_server xattr_create xattr_dontfollow xattr_get xattr_list xattr_remove xattr_replace xattr_root xattr_set xattr_supported xdiff_file_bdiff xdiff_file_bdiff_size xdiff_file_bpatch xdiff_file_diff xdiff_file_diff_binary xdiff_file_merge3 xdiff_file_patch xdiff_file_patch_binary xdiff_file_rabdiff xdiff_patch_normal xdiff_patch_reverse xdiff_string_bdiff xdiff_string_bdiff_size xdiff_string_bpatch xdiff_string_diff xdiff_string_diff_binary xdiff_string_merge3 xdiff_string_patch xdiff_string_patch_binary xdiff_string_rabdiff xhprof_disable xhprof_enable xhprof_sample_disable xhprof_sample_enable xml_attribute_cdata xml_attribute_decl_node xml_attribute_entity xml_attribute_enumeration xml_attribute_id xml_attribute_idref xml_attribute_idrefs xml_attribute_nmtoken xml_attribute_nmtokens xml_attribute_node xml_attribute_notation xml_cdata_section_node xml_comment_node xml_document_frag_node xml_document_node xml_document_type_node xml_dtd_node xml_element_decl_node xml_element_node xml_entity_decl_node xml_entity_node xml_entity_ref_node xml_error_async_entity xml_error_attribute_external_entity_ref xml_error_bad_char_ref xml_error_binary_entity_ref xml_error_duplicate_attribute xml_error_external_entity_handling xml_error_incorrect_encoding xml_error_invalid_token xml_error_junk_after_doc_element xml_error_misplaced_xml_pi xml_error_no_elements xml_error_no_memory xml_error_none xml_error_param_entity_ref xml_error_partial_char xml_error_recursive_entity_ref xml_error_string xml_error_syntax xml_error_tag_mismatch xml_error_unclosed_cdata_section xml_error_unclosed_token xml_error_undefined_entity xml_error_unknown_encoding xml_get_current_byte_index xml_get_current_column_number xml_get_current_line_number xml_get_error_code xml_html_document_node xml_local_namespace xml_namespace_decl_node xml_notation_node xml_option_case_folding xml_option_skip_tagstart xml_option_skip_white xml_option_target_encoding xml_parse xml_parse_into_struct xml_parser_create xml_parser_create_ns xml_parser_free xml_parser_get_option xml_parser_set_option xml_pi_node xml_sax_impl xml_set_character_data_handler xml_set_default_handler xml_set_element_handler xml_set_end_namespace_decl_handler xml_set_external_entity_ref_handler xml_set_notation_decl_handler xml_set_object xml_set_processing_instruction_handler xml_set_start_namespace_decl_handler xml_set_unparsed_entity_decl_handler xml_text_node xmlrpc_decode xmlrpc_decode_request xmlrpc_encode xmlrpc_encode_request xmlrpc_get_type xmlrpc_is_fault xmlrpc_parse_method_descriptions xmlrpc_server_add_introspection_data xmlrpc_server_call_method xmlrpc_server_create xmlrpc_server_destroy xmlrpc_server_register_introspection_callback xmlrpc_server_register_method xmlrpc_set_type xmlwriter_end_attribute xmlwriter_end_cdata xmlwriter_end_comment xmlwriter_end_document xmlwriter_end_dtd xmlwriter_end_dtd_attlist xmlwriter_end_dtd_element xmlwriter_end_dtd_entity xmlwriter_end_element xmlwriter_end_pi xmlwriter_flush xmlwriter_full_end_element xmlwriter_open_memory xmlwriter_open_uri xmlwriter_output_memory xmlwriter_set_indent xmlwriter_set_indent_string xmlwriter_start_attribute xmlwriter_start_attribute_ns xmlwriter_start_cdata xmlwriter_start_comment xmlwriter_start_document xmlwriter_start_dtd xmlwriter_start_dtd_attlist xmlwriter_start_dtd_element xmlwriter_start_dtd_entity xmlwriter_start_element xmlwriter_start_element_ns xmlwriter_start_pi xmlwriter_text xmlwriter_write_attribute xmlwriter_write_attribute_ns xmlwriter_write_cdata xmlwriter_write_comment xmlwriter_write_dtd xmlwriter_write_dtd_attlist xmlwriter_write_dtd_element xmlwriter_write_dtd_entity xmlwriter_write_element xmlwriter_write_element_ns xmlwriter_write_pi xmlwriter_write_raw xor xsd_1999_namespace xsd_1999_timeinstant xsd_anytype xsd_anyuri xsd_anyxml xsd_base64binary xsd_boolean xsd_byte xsd_date xsd_datetime xsd_decimal xsd_double xsd_duration xsd_entities xsd_entity xsd_float xsd_gday xsd_gmonth xsd_gmonthday xsd_gyear xsd_gyearmonth xsd_hexbinary xsd_id xsd_idref xsd_idrefs xsd_int xsd_integer xsd_language xsd_long xsd_name xsd_namespace xsd_ncname xsd_negativeinteger xsd_nmtoken xsd_nmtokens xsd_nonnegativeinteger xsd_nonpositiveinteger xsd_normalizedstring xsd_notation xsd_positiveinteger xsd_qname xsd_short xsd_string xsd_time xsd_token xsd_unsignedbyte xsd_unsignedint xsd_unsignedlong xsd_unsignedshort xsl_clone_always xsl_clone_auto xsl_clone_never xsl_secpref_create_directory xsl_secpref_default xsl_secpref_none xsl_secpref_read_file xsl_secpref_read_network xsl_secpref_write_file xsl_secpref_write_network yaml_any_break yaml_any_encoding yaml_any_scalar_style yaml_bool_tag yaml_cr_break yaml_crln_break yaml_double_quoted_scalar_style yaml_emit yaml_emit_file yaml_float_tag yaml_folded_scalar_style yaml_int_tag yaml_literal_scalar_style yaml_ln_break yaml_map_tag yaml_null_tag yaml_parse yaml_parse_file yaml_parse_url yaml_php_tag yaml_plain_scalar_style yaml_seq_tag yaml_single_quoted_scalar_style yaml_str_tag yaml_timestamp_tag yaml_utf16be_encoding yaml_utf16le_encoding yaml_utf8_encoding yesexpr yesstr yield zend_debug_build zend_logo_guid zend_multibyte zend_thread_id zend_thread_safe zend_version zip_close zip_entry_close zip_entry_compressedsize zip_entry_compressionmethod zip_entry_filesize zip_entry_name zip_entry_open zip_entry_read zip_open zip_read zlib_decode zlib_encode zlib_encoding_deflate zlib_encoding_gzip zlib_encoding_raw zlib_get_coding_type"
"__autoload __class__ __compiler_halt_offset__ __construct __destruct __dir__ __file__ __function__ __halt_compiler __line__ __method__ __namespace__ __sleep __trait__ __wakeup _cookie _files _get _post abday_1 abday_2 abday_3 abday_4 abday_5 abday_6 abday_7 abmon_1 abmon_10 abmon_11 abmon_12 abmon_2 abmon_3 abmon_4 abmon_5 abmon_6 abmon_7 abmon_8 abmon_9 abs abstract acos acosh addcslashes addslashes af_inet af_inet6 af_unix al_bits al_buffer al_channels al_cone_inner_angle al_cone_outer_angle al_cone_outer_gain al_direction al_false al_format_mono16 al_format_mono8 al_format_stereo16 al_format_stereo8 al_frequency al_gain al_initial al_looping al_max_distance al_max_gain al_min_gain al_orientation al_paused al_pitch al_playing al_position al_reference_distance al_rolloff_factor al_size al_source_relative al_source_state al_stopped al_true al_velocity alc_frequency alc_refresh alc_sync alt_digits am_str and apache_child_terminate apache_get_modules apache_get_version apache_getenv apache_lookup_uri apache_map apache_note apache_request_headers apache_reset_timeout apache_response_headers apache_setenv apc_add apc_bin_dump apc_bin_dumpfile apc_bin_load apc_bin_loadfile apc_bin_verify_crc32 apc_bin_verify_md5 apc_cache_info apc_cas apc_clear_cache apc_compile_file apc_dec apc_define_constants apc_delete apc_delete_file apc_exists apc_fetch apc_inc apc_iter_all apc_iter_atime apc_iter_ctime apc_iter_device apc_iter_dtime apc_iter_filename apc_iter_inode apc_iter_key apc_iter_md5 apc_iter_mem_size apc_iter_mtime apc_iter_none apc_iter_num_hits apc_iter_refcount apc_iter_ttl apc_iter_type apc_iter_value apc_list_active apc_list_deleted apc_load_constants apc_sma_info apc_store apd_breakpoint apd_callstack apd_clunk apd_continue apd_croak apd_dump_function_table apd_dump_persistent_resources apd_dump_regular_resources apd_echo apd_get_active_symbols apd_set_pprof_trace apd_set_session apd_set_session_trace apd_set_session_trace_socket apd_version args_trace array array_change_key_case array_chunk array_column array_combine array_count_values array_diff array_diff_assoc array_diff_key array_diff_uassoc array_diff_ukey array_fill array_fill_keys array_filter array_filter_use_both array_filter_use_key array_flip array_intersect array_intersect_assoc array_intersect_key array_intersect_uassoc array_intersect_ukey array_key_exists array_keys array_map array_merge array_merge_recursive array_multisort array_pad array_pop array_product array_push array_rand array_reduce array_replace array_replace_recursive array_reverse array_search array_shift array_slice array_sort array_splice array_sum array_udiff array_udiff_assoc array_udiff_uassoc array_uintersect array_uintersect_assoc array_uintersect_uassoc array_unique array_unshift array_values array_walk array_walk_recursive arrayaccess arrayiterator arrayobject arsort as asin asinh asort assert assert_active assert_bail assert_callback assert_options assert_quiet_eval assert_warning assignment_trace atan atan2 atanh base64_decode base64_encode base_convert basename bbcode_add_element bbcode_add_smiley bbcode_arg_double_quote bbcode_arg_html_quote bbcode_arg_quote_escaping bbcode_arg_single_quote bbcode_auto_correct bbcode_correct_reopen_tags bbcode_create bbcode_default_smileys_off bbcode_default_smileys_on bbcode_destroy bbcode_disable_tree_build bbcode_flags_arg_parsing bbcode_flags_cdata_not_allowed bbcode_flags_deny_reopen_child bbcode_flags_one_open_per_level bbcode_flags_remove_if_empty bbcode_flags_smileys_off bbcode_flags_smileys_on bbcode_force_smileys_off bbcode_parse bbcode_set_arg_parser bbcode_set_flags bbcode_set_flags_add bbcode_set_flags_remove bbcode_set_flags_set bbcode_smileys_case_insensitive bbcode_type_arg bbcode_type_noarg bbcode_type_optarg bbcode_type_root bbcode_type_single bcadd bccomp bcdiv bcmod bcmul bcompiler_load bcompiler_load_exe bcompiler_parse_class bcompiler_read bcompiler_write_class bcompiler_write_constant bcompiler_write_exe_footer bcompiler_write_file bcompiler_write_footer bcompiler_write_function bcompiler_write_functions_from_file bcompiler_write_header bcompiler_write_included_filename bcpow bcpowmod bcscale bcsqrt bcsub bin2hex bind_textdomain_codeset bindec bindtextdomain blenc_encrypt blenc_ext_version bool boolean boolval break bson_decode bson_encode bus_adraln bus_adrerr bus_objerr bzclose bzcompress bzdecompress bzerrno bzerror bzerrstr bzflush bzopen bzread bzwrite cairo_antialias_default cairo_antialias_gray cairo_antialias_none cairo_antialias_subpixel cairo_content_alpha cairo_content_color cairo_content_color_alpha cairo_create cairo_extend_none cairo_extend_pad cairo_extend_reflect cairo_extend_repeat cairo_fill_rule_even_odd cairo_fill_rule_winding cairo_filter_best cairo_filter_bilinear cairo_filter_fast cairo_filter_gaussian cairo_filter_good cairo_filter_nearest cairo_font_face_get_type cairo_font_face_status cairo_font_options_create cairo_font_options_equal cairo_font_options_get_antialias cairo_font_options_get_hint_metrics cairo_font_options_get_hint_style cairo_font_options_get_subpixel_order cairo_font_options_hash cairo_font_options_merge cairo_font_options_set_antialias cairo_font_options_set_hint_metrics cairo_font_options_set_hint_style cairo_font_options_set_subpixel_order cairo_font_options_status cairo_font_slant_italic cairo_font_slant_normal cairo_font_slant_oblique cairo_font_type_ft cairo_font_type_quartz cairo_font_type_toy cairo_font_type_win32 cairo_font_weight_bold cairo_font_weight_normal cairo_format_a1 cairo_format_a8 cairo_format_argb32 cairo_format_rgb24 cairo_format_stride_for_width cairo_hint_metrics_default cairo_hint_metrics_off cairo_hint_metrics_on cairo_hint_style_default cairo_hint_style_full cairo_hint_style_medium cairo_hint_style_none cairo_hint_style_slight cairo_image_surface_create cairo_image_surface_create_for_data cairo_image_surface_create_from_png cairo_image_surface_get_data cairo_image_surface_get_format cairo_image_surface_get_height cairo_image_surface_get_stride cairo_image_surface_get_width cairo_line_cap_butt cairo_line_cap_round cairo_line_cap_square cairo_line_join_bevel cairo_line_join_miter cairo_line_join_round cairo_matrix_create_scale cairo_matrix_create_translate cairo_matrix_invert cairo_matrix_multiply cairo_matrix_rotate cairo_matrix_transform_distance cairo_matrix_transform_point cairo_matrix_translate cairo_operator_add cairo_operator_atop cairo_operator_clear cairo_operator_dest cairo_operator_dest_atop cairo_operator_dest_in cairo_operator_dest_out cairo_operator_dest_over cairo_operator_in cairo_operator_out cairo_operator_over cairo_operator_saturate cairo_operator_source cairo_operator_xor cairo_pattern_add_color_stop_rgb cairo_pattern_add_color_stop_rgba cairo_pattern_create_for_surface cairo_pattern_create_linear cairo_pattern_create_radial cairo_pattern_create_rgb cairo_pattern_create_rgba cairo_pattern_get_color_stop_count cairo_pattern_get_color_stop_rgba cairo_pattern_get_extend cairo_pattern_get_filter cairo_pattern_get_linear_points cairo_pattern_get_matrix cairo_pattern_get_radial_circles cairo_pattern_get_rgba cairo_pattern_get_surface cairo_pattern_get_type cairo_pattern_set_extend cairo_pattern_set_filter cairo_pattern_set_matrix cairo_pattern_status cairo_pattern_type_linear cairo_pattern_type_radial cairo_pattern_type_solid cairo_pattern_type_surface cairo_pdf_surface_create cairo_pdf_surface_set_size cairo_ps_get_levels cairo_ps_level_2 cairo_ps_level_3 cairo_ps_level_to_string cairo_ps_surface_create cairo_ps_surface_dsc_begin_page_setup cairo_ps_surface_dsc_begin_setup cairo_ps_surface_dsc_comment cairo_ps_surface_get_eps cairo_ps_surface_restrict_to_level cairo_ps_surface_set_eps cairo_ps_surface_set_size cairo_scaled_font_create cairo_scaled_font_extents cairo_scaled_font_get_ctm cairo_scaled_font_get_font_face cairo_scaled_font_get_font_matrix cairo_scaled_font_get_font_options cairo_scaled_font_get_scale_matrix cairo_scaled_font_get_type cairo_scaled_font_glyph_extents cairo_scaled_font_status cairo_scaled_font_text_extents cairo_status_clip_not_representable cairo_status_file_not_found cairo_status_invalid_content cairo_status_invalid_dash cairo_status_invalid_dsc_comment cairo_status_invalid_format cairo_status_invalid_index cairo_status_invalid_matrix cairo_status_invalid_path_data cairo_status_invalid_pop_group cairo_status_invalid_restore cairo_status_invalid_status cairo_status_invalid_stride cairo_status_invalid_string cairo_status_invalid_visual cairo_status_no_current_point cairo_status_no_memory cairo_status_null_pointer cairo_status_pattern_type_mismatch cairo_status_read_error cairo_status_success cairo_status_surface_finished cairo_status_surface_type_mismatch cairo_status_temp_file_error cairo_status_write_error cairo_subpixel_order_bgr cairo_subpixel_order_default cairo_subpixel_order_rgb cairo_subpixel_order_vbgr cairo_subpixel_order_vrgb cairo_surface_copy_page cairo_surface_create_similar cairo_surface_finish cairo_surface_flush cairo_surface_get_content cairo_surface_get_device_offset cairo_surface_get_font_options cairo_surface_get_type cairo_surface_mark_dirty cairo_surface_mark_dirty_rectangle cairo_surface_set_device_offset cairo_surface_set_fallback_resolution cairo_surface_show_page cairo_surface_status cairo_surface_type_beos cairo_surface_type_directfb cairo_surface_type_glitz cairo_surface_type_image cairo_surface_type_os2 cairo_surface_type_pdf cairo_surface_type_ps cairo_surface_type_quartz cairo_surface_type_quartz_image cairo_surface_type_svg cairo_surface_type_win32 cairo_surface_type_win32_printing cairo_surface_type_xcb cairo_surface_type_xlib cairo_surface_write_to_png cairo_svg_surface_create cairo_svg_surface_restrict_to_version cairo_svg_version_1_1 cairo_svg_version_1_2
 cairo_svg_version_to_string cal_days_in_month cal_dow_dayno cal_dow_long cal_dow_short cal_easter_always_gregorian cal_easter_always_julian cal_easter_default cal_easter_roman cal_french cal_from_jd cal_gregorian cal_info cal_jewish cal_jewish_add_alafim cal_jewish_add_alafim_geresh cal_jewish_add_gereshayim cal_julian cal_month_french cal_month_gregorian_long cal_month_gregorian_short cal_month_jewish cal_month_julian_long cal_month_julian_short cal_num_cals cal_to_jd calcul_hmac calculhmac call_user_func call_user_func_array call_user_method call_user_method_array callable case case_lower case_upper catch ceil cfunction char_max chdb_create chdir checkdate checkdnsrr chgrp chmod chop chown chr chroot chunk_split cl_expunge class class_alias class_exists class_implements class_parents class_uses cld_continued cld_dumped cld_exited cld_killed cld_stopped cld_trapped clearstatcache cli_get_process_title cli_set_process_title clone closedir closelog clsctx_all clsctx_inproc_handler clsctx_inproc_server clsctx_local_server clsctx_remote_server clsctx_server codeset collator_asort collator_compare collator_create collator_get_attribute collator_get_error_code collator_get_error_message collator_get_locale collator_get_sort_key collator_get_strength collator_set_attribute collator_set_strength collator_sort collator_sort_with_sort_keys com_create_guid com_event_sink com_get com_get_active_object com_invoke com_load com_load_typelib com_message_pump com_print_typeinfo com_propget com_propput com_set compact connection_aborted connection_normal connection_status connection_timeout const constant continue convert_cyr_string convert_uudecode convert_uuencode copy cos cosh count count_chars count_normal count_recursive cp_acp cp_maccp cp_move cp_oemcp cp_symbol cp_thread_acp cp_uid cp_utf7 cp_utf8 crc32 create_function credits_all credits_docs credits_fullpage credits_general credits_group credits_modules credits_qa credits_sapi crncystr crypt crypt_blowfish crypt_ext_des crypt_md5 crypt_salt_length crypt_sha256 crypt_sha512 crypt_std_des ctype_alnum ctype_alpha ctype_cntrl ctype_digit ctype_graph ctype_lower ctype_print ctype_punct ctype_space ctype_upper ctype_xdigit cubrid_affected_rows cubrid_assoc cubrid_async cubrid_autocommit_false cubrid_autocommit_true cubrid_bind cubrid_both cubrid_client_encoding cubrid_close cubrid_close_prepare cubrid_close_request cubrid_col_get cubrid_col_size cubrid_column_names cubrid_column_types cubrid_commit cubrid_connect cubrid_connect_with_url cubrid_current_oid cubrid_cursor_current cubrid_cursor_error cubrid_cursor_first cubrid_cursor_last cubrid_cursor_success cubrid_data_seek cubrid_db_name cubrid_disconnect cubrid_drop cubrid_errno cubrid_error cubrid_error_code cubrid_error_code_facility cubrid_error_msg cubrid_exec_query_all cubrid_execute cubrid_facility_cas cubrid_facility_cci cubrid_facility_client cubrid_facility_dbms cubrid_fetch cubrid_fetch_array cubrid_fetch_assoc cubrid_fetch_field cubrid_fetch_lengths cubrid_fetch_object cubrid_fetch_row cubrid_field_flags cubrid_field_len cubrid_field_name cubrid_field_seek cubrid_field_table cubrid_field_type cubrid_free_result cubrid_get cubrid_get_autocommit cubrid_get_charset cubrid_get_class_name cubrid_get_client_info cubrid_get_db_parameter cubrid_get_query_timeout cubrid_get_server_info cubrid_include_oid cubrid_insert_id cubrid_is_instance cubrid_list_dbs cubrid_lob cubrid_lob2_bind cubrid_lob2_close cubrid_lob2_export cubrid_lob2_import cubrid_lob2_new cubrid_lob2_read cubrid_lob2_seek cubrid_lob2_seek64 cubrid_lob2_size cubrid_lob2_size64 cubrid_lob2_tell cubrid_lob2_tell64 cubrid_lob2_write cubrid_lob_close cubrid_lob_export cubrid_lob_get cubrid_lob_send cubrid_lob_size cubrid_lock_read cubrid_lock_write cubrid_move_cursor cubrid_next_result cubrid_no_more_data cubrid_num cubrid_num_cols cubrid_num_fields cubrid_num_rows cubrid_object cubrid_param_isolation_level cubrid_param_lock_timeout cubrid_pconnect cubrid_pconnect_with_url cubrid_ping cubrid_prepare cubrid_put cubrid_query cubrid_real_escape_string cubrid_result cubrid_rollback cubrid_sch_attr_privilege cubrid_sch_attribute cubrid_sch_class cubrid_sch_class_attribute cubrid_sch_class_method cubrid_sch_class_privilege cubrid_sch_constraint cubrid_sch_cross_reference cubrid_sch_direct_super_class cubrid_sch_exported_keys cubrid_sch_imported_keys cubrid_sch_method cubrid_sch_method_file cubrid_sch_primary_key cubrid_sch_query_spec cubrid_sch_subclass cubrid_sch_superclass cubrid_sch_trigger cubrid_sch_vclass cubrid_schema cubrid_seq_drop cubrid_seq_insert cubrid_seq_put cubrid_set_add cubrid_set_autocommit cubrid_set_db_parameter cubrid_set_drop cubrid_set_query_timeout cubrid_unbuffered_query cubrid_version curl_close curl_copy_handle curl_errno curl_error curl_escape curl_exec curl_file_create curl_fnmatchfunc_fail curl_fnmatchfunc_match curl_fnmatchfunc_nomatch curl_getinfo curl_http_version_1_0 curl_http_version_1_1 curl_http_version_2_0 curl_http_version_none curl_init curl_ipresolve_v4 curl_ipresolve_v6 curl_ipresolve_whatever curl_lock_data_cookie curl_lock_data_dns curl_lock_data_ssl_session curl_multi_add_handle curl_multi_close curl_multi_exec curl_multi_getcontent curl_multi_info_read curl_multi_init curl_multi_remove_handle curl_multi_select curl_multi_setopt curl_multi_strerror curl_netrc_ignored curl_netrc_optional curl_netrc_required curl_pause curl_readfunc_pause curl_reset curl_rtspreq_announce curl_rtspreq_describe curl_rtspreq_get_parameter curl_rtspreq_options curl_rtspreq_pause curl_rtspreq_play curl_rtspreq_receive curl_rtspreq_record curl_rtspreq_set_parameter curl_rtspreq_setup curl_rtspreq_teardown curl_setopt curl_setopt_array curl_share_close curl_share_init curl_share_setopt curl_sslversion_default curl_sslversion_sslv2 curl_sslversion_sslv3 curl_sslversion_tlsv1 curl_sslversion_tlsv1_0 curl_sslversion_tlsv1_1 curl_sslversion_tlsv1_2 curl_strerror curl_timecond_ifmodsince curl_timecond_ifunmodsince curl_timecond_lastmod curl_timecond_none curl_tlsauth_srp curl_unescape curl_version curl_version_http2 curl_version_ipv6 curl_version_kerberos4 curl_version_libz curl_version_ssl curl_wrappers_enabled curl_writefunc_pause curlauth_any curlauth_anysafe curlauth_basic curlauth_digest curlauth_digest_ie curlauth_gssnegotiate curlauth_none curlauth_ntlm curlauth_only curlclosepolicy_callback curlclosepolicy_least_recently_used curlclosepolicy_least_traffic curlclosepolicy_oldest curlclosepolicy_slowest curle_aborted_by_callback curle_bad_calling_order curle_bad_content_encoding curle_bad_download_resume curle_bad_function_argument curle_bad_password_entered curle_couldnt_connect curle_couldnt_resolve_host curle_couldnt_resolve_proxy curle_failed_init curle_file_couldnt_read_file curle_filesize_exceeded curle_ftp_access_denied curle_ftp_bad_download_resume curle_ftp_cant_get_host curle_ftp_cant_reconnect curle_ftp_couldnt_get_size curle_ftp_couldnt_retr_file curle_ftp_couldnt_set_ascii curle_ftp_couldnt_set_binary curle_ftp_couldnt_stor_file curle_ftp_couldnt_use_rest curle_ftp_partial_file curle_ftp_port_failed curle_ftp_quote_error curle_ftp_ssl_failed curle_ftp_user_password_incorrect curle_ftp_weird_227_format curle_ftp_weird_pass_reply curle_ftp_weird_pasv_reply curle_ftp_weird_server_reply curle_ftp_weird_user_reply curle_ftp_write_error curle_function_not_found curle_got_nothing curle_http_not_found curle_http_port_failed curle_http_post_error curle_http_range_error curle_http_returned_error curle_ldap_cannot_bind curle_ldap_invalid_url curle_ldap_search_failed curle_library_not_found curle_malformat_user curle_obsolete curle_ok curle_operation_timedout curle_operation_timeouted curle_out_of_memory curle_partial_file curle_read_error curle_recv_error curle_send_error curle_share_in_use curle_ssh curle_ssl_cacert curle_ssl_certproblem curle_ssl_cipher curle_ssl_connect_error curle_ssl_engine_notfound curle_ssl_engine_setfailed curle_ssl_peer_certificate curle_telnet_option_syntax curle_too_many_redirects curle_unknown_telnet_option curle_unsupported_protocol curle_url_malformat curle_url_malformat_user curle_write_error curlftpauth_default curlftpauth_ssl curlftpauth_tls curlftpmethod_multicwd curlftpmethod_nocwd curlftpmethod_singlecwd curlftpssl_all curlftpssl_ccc_active curlftpssl_ccc_none curlftpssl_ccc_passive curlftpssl_control curlftpssl_none curlftpssl_try curlgssapi_delegation_flag curlgssapi_delegation_policy_flag curlinfo_appconnect_time curlinfo_certinfo curlinfo_condition_unmet curlinfo_connect_time curlinfo_content_length_download curlinfo_content_length_upload curlinfo_content_type curlinfo_cookielist curlinfo_effective_url curlinfo_filetime curlinfo_ftp_entry_path curlinfo_header_out curlinfo_header_size curlinfo_http_code curlinfo_http_connectcode curlinfo_httpauth_avail curlinfo_lastone curlinfo_local_ip curlinfo_local_port curlinfo_namelookup_time curlinfo_num_connects curlinfo_os_errno curlinfo_pretransfer_time curlinfo_primary_ip curlinfo_primary_port curlinfo_private curlinfo_proxyauth_avail curlinfo_redirect_count curlinfo_redirect_time curlinfo_redirect_url curlinfo_request_size curlinfo_response_code curlinfo_rtsp_client_cseq curlinfo_rtsp_cseq_recv curlinfo_rtsp_server_cseq curlinfo_rtsp_session_id curlinfo_size_download curlinfo_size_upload curlinfo_speed_download curlinfo_speed_upload curlinfo_ssl_engines curlinfo_ssl_verifyresult curlinfo_starttransfer_time curlinfo_total_time curlm_bad_easy_handle curlm_bad_handle curlm_call_multi_perform curlm_internal_error curlm_ok curlm_out_of_memory curlmopt_maxconnects curlmopt_pipelining curlmsg_done curlopt_accept_encoding curlopt_accepttimeout_ms curlopt_address_scope curlopt_append curlopt_autoreferer curlopt_binarytransfer curlopt_buffersize curlopt_cainfo
 curlopt_capath curlopt_certinfo curlopt_closepolicy curlopt_connect_only curlopt_connecttimeout curlopt_connecttimeout_ms curlopt_cookie curlopt_cookiefile curlopt_cookiejar curlopt_cookielist curlopt_cookiesession curlopt_crlf curlopt_crlfile curlopt_customrequest curlopt_dirlistonly curlopt_dns_cache_timeout curlopt_dns_servers curlopt_dns_use_global_cache curlopt_egdsocket curlopt_encoding curlopt_failonerror curlopt_file curlopt_filetime curlopt_fnmatch_function curlopt_followlocation curlopt_forbid_reuse curlopt_fresh_connect curlopt_ftp_account curlopt_ftp_alternative_to_user curlopt_ftp_create_missing_dirs curlopt_ftp_filemethod curlopt_ftp_response_timeout curlopt_ftp_skip_pasv_ip curlopt_ftp_ssl curlopt_ftp_ssl_ccc curlopt_ftp_use_eprt curlopt_ftp_use_epsv curlopt_ftp_use_pret curlopt_ftpappend curlopt_ftpascii curlopt_ftplistonly curlopt_ftpport curlopt_ftpsslauth curlopt_gssapi_delegation curlopt_header curlopt_headerfunction curlopt_http200aliases curlopt_http_content_decoding curlopt_http_transfer_decoding curlopt_http_version curlopt_httpauth curlopt_httpget curlopt_httpheader curlopt_httpproxytunnel curlopt_ignore_content_length curlopt_infile curlopt_infilesize curlopt_interface curlopt_ipresolve curlopt_issuercert curlopt_keypasswd curlopt_krb4level curlopt_krblevel curlopt_localport curlopt_localportrange curlopt_low_speed_limit curlopt_low_speed_time curlopt_mail_auth curlopt_mail_from curlopt_mail_rcpt curlopt_max_recv_speed_large curlopt_max_send_speed_large curlopt_maxconnects curlopt_maxfilesize curlopt_maxredirs curlopt_mute curlopt_netrc curlopt_netrc_file curlopt_new_directory_perms curlopt_new_file_perms curlopt_nobody curlopt_noprogress curlopt_noproxy curlopt_nosignal curlopt_passwdfunction curlopt_password curlopt_port curlopt_post curlopt_postfields curlopt_postquote curlopt_postredir curlopt_prequote curlopt_private curlopt_progressfunction curlopt_protocols curlopt_proxy curlopt_proxy_transfer_mode curlopt_proxyauth curlopt_proxypassword curlopt_proxyport curlopt_proxytype curlopt_proxyusername curlopt_proxyuserpwd curlopt_put curlopt_quote curlopt_random_file curlopt_range curlopt_readdata curlopt_readfunction curlopt_redir_protocols curlopt_referer curlopt_resolve curlopt_resume_from curlopt_returntransfer curlopt_rtsp_client_cseq curlopt_rtsp_request curlopt_rtsp_server_cseq curlopt_rtsp_session_id curlopt_rtsp_stream_uri curlopt_rtsp_transport curlopt_safe_upload curlopt_share curlopt_socks5_gssapi_nec curlopt_socks5_gssapi_service curlopt_ssh_auth_types curlopt_ssh_host_public_key_md5 curlopt_ssh_knownhosts curlopt_ssh_private_keyfile curlopt_ssh_public_keyfile curlopt_ssl_cipher_list curlopt_ssl_options curlopt_ssl_sessionid_cache curlopt_ssl_verifyhost curlopt_ssl_verifypeer curlopt_sslcert curlopt_sslcertpasswd curlopt_sslcerttype curlopt_sslengine curlopt_sslengine_default curlopt_sslkey curlopt_sslkeypasswd curlopt_sslkeytype curlopt_sslversion curlopt_stderr curlopt_tcp_keepalive curlopt_tcp_keepidle curlopt_tcp_keepintvl curlopt_tcp_nodelay curlopt_telnetoptions curlopt_tftp_blksize curlopt_timecondition curlopt_timeout curlopt_timeout_ms curlopt_timevalue curlopt_tlsauth_password curlopt_tlsauth_type curlopt_tlsauth_username curlopt_transfer_encoding curlopt_transfertext curlopt_unrestricted_auth curlopt_upload curlopt_url curlopt_use_ssl curlopt_useragent curlopt_username curlopt_userpwd curlopt_verbose curlopt_wildcardmatch curlopt_writefunction curlopt_writeheader curlpause_all curlpause_cont curlpause_recv curlpause_recv_cont curlpause_send curlpause_send_cont curlproto_all curlproto_dict curlproto_file curlproto_ftp curlproto_ftps curlproto_gopher curlproto_http curlproto_https curlproto_imap curlproto_imaps curlproto_ldap curlproto_ldaps curlproto_pop3 curlproto_pop3s curlproto_rtmp curlproto_rtmpe curlproto_rtmps curlproto_rtmpt curlproto_rtmpte curlproto_rtmpts curlproto_rtsp curlproto_scp curlproto_sftp curlproto_smtp curlproto_smtps curlproto_telnet curlproto_tftp curlproxy_http curlproxy_socks4 curlproxy_socks4a curlproxy_socks5 curlproxy_socks5_hostname curlshopt_none curlshopt_share curlshopt_unshare curlssh_auth_any curlssh_auth_default curlssh_auth_host curlssh_auth_keyboard curlssh_auth_none curlssh_auth_password curlssh_auth_publickey curlsslopt_allow_beast curlusessl_all curlusessl_control curlusessl_none curlusessl_try curlversion_now currency_symbol current cyrus_authenticate cyrus_bind cyrus_callback_noliteral cyrus_callback_numbered cyrus_close cyrus_conn_initialresponse cyrus_conn_nonsyncliteral cyrus_connect cyrus_query cyrus_unbind d_fmt d_t_fmt date date_add date_atom date_cookie date_create date_create_from_format date_create_immutable date_create_immutable_from_format date_date_set date_default_timezone_get date_default_timezone_set date_diff date_format date_get_last_errors date_interval_create_from_date_string date_interval_format date_iso8601 date_isodate_set date_modify date_offset_get date_parse date_parse_from_format date_rfc1036 date_rfc1123 date_rfc2822 date_rfc3339 date_rfc822 date_rfc850 date_rss date_sub date_sun_info date_sunrise date_sunset date_time_set date_timestamp_get date_timestamp_set date_timezone_get date_timezone_set date_w3c datefmt_create datefmt_format datefmt_get_calendar datefmt_get_datetype datefmt_get_error_code datefmt_get_error_message datefmt_get_locale datefmt_get_pattern datefmt_get_timetype datefmt_get_timezone_id datefmt_is_lenient datefmt_localtime datefmt_parse datefmt_set_calendar datefmt_set_lenient datefmt_set_pattern datefmt_set_timezone_id day_1 day_2 day_3 day_4 day_5 day_6 day_7 db2_autocommit db2_autocommit_off db2_autocommit_on db2_binary db2_bind_param db2_case_lower db2_case_natural db2_case_upper db2_char db2_client_info db2_close db2_column_privileges db2_columns db2_commit db2_conn_error db2_conn_errormsg db2_connect db2_convert db2_cursor_type db2_deferred_prepare_off db2_deferred_prepare_on db2_double db2_escape_string db2_exec db2_execute db2_fetch_array db2_fetch_assoc db2_fetch_both db2_fetch_object db2_fetch_row db2_field_display_size db2_field_name db2_field_num db2_field_precision db2_field_scale db2_field_type db2_field_width db2_foreign_keys db2_forward_only db2_free_result db2_free_stmt db2_get_option db2_last_insert_id db2_lob_read db2_long db2_next_result db2_num_fields db2_num_rows db2_param_file db2_param_in db2_param_inout db2_param_out db2_passthru db2_pclose db2_pconnect db2_prepare db2_primary_keys db2_procedure_columns db2_procedures db2_result db2_rollback db2_scrollable db2_server_info db2_set_option db2_special_columns db2_statistics db2_stmt_error db2_stmt_errormsg db2_table_privileges db2_tables dba_close dba_delete dba_exists dba_fetch dba_firstkey dba_handlers dba_insert dba_key_split dba_list dba_nextkey dba_open dba_optimize dba_popen dba_replace dba_sync dbase_add_record dbase_close dbase_create dbase_delete_record dbase_get_header_info dbase_get_record dbase_get_record_with_names dbase_numfields dbase_numrecords dbase_open dbase_pack dbase_replace_record dbplus_add dbplus_aql dbplus_chdir dbplus_close dbplus_curr dbplus_err_close dbplus_err_corrupt_tuple dbplus_err_crc dbplus_err_create dbplus_err_dbparse dbplus_err_dbpreexit dbplus_err_dbrunerr dbplus_err_duplicate dbplus_err_empty dbplus_err_eoscan dbplus_err_fifo dbplus_err_length dbplus_err_locked dbplus_err_lseek dbplus_err_magic dbplus_err_malloc dbplus_err_nidx dbplus_err_noerr dbplus_err_nolock dbplus_err_nusers dbplus_err_ontrap dbplus_err_open dbplus_err_panic dbplus_err_perm dbplus_err_pgsize dbplus_err_pipe dbplus_err_preexit dbplus_err_preproc dbplus_err_read dbplus_err_restricted dbplus_err_tcl dbplus_err_unknown dbplus_err_user dbplus_err_version dbplus_err_wait dbplus_err_warning0 dbplus_err_wlocked dbplus_err_wopen dbplus_err_write dbplus_errcode dbplus_errno dbplus_find dbplus_first dbplus_flush dbplus_freealllocks dbplus_freelock dbplus_freerlocks dbplus_getlock dbplus_getunique dbplus_info dbplus_last dbplus_lockrel dbplus_next dbplus_open dbplus_prev dbplus_rchperm dbplus_rcreate dbplus_rcrtexact dbplus_rcrtlike dbplus_resolve dbplus_restorepos dbplus_rkeys dbplus_ropen dbplus_rquery dbplus_rrename dbplus_rsecindex dbplus_runlink dbplus_rzap dbplus_savepos dbplus_setindex dbplus_setindexbynumber dbplus_sql dbplus_tcl dbplus_tremove dbplus_undo dbplus_undoprepare dbplus_unlockrel dbplus_unselect dbplus_update dbplus_xlockrel dbplus_xunlockrel dbx_close dbx_cmp_asc dbx_cmp_desc dbx_cmp_native dbx_cmp_number dbx_cmp_text dbx_colnames_lowercase dbx_colnames_unchanged dbx_colnames_uppercase dbx_compare dbx_connect dbx_error dbx_escape_string dbx_fbsql dbx_fetch_row dbx_mssql dbx_mysql dbx_oci8 dbx_odbc dbx_persistent dbx_pgsql dbx_query dbx_result_assoc dbx_result_index dbx_result_info dbx_result_unbuffered dbx_sort dbx_sqlite dbx_sybasect dcgettext dcngettext debug_backtrace debug_backtrace_ignore_args debug_backtrace_provide_object debug_print_backtrace debug_zval_dump decbin dechex decimal_point declare decoct default default_include_path define define_syslog_variables defined deg2rad delete dgettext die dio_close dio_fcntl dio_open dio_read dio_seek dio_stat dio_tcsetattr dio_truncate dio_write dir directory directory_separator dirname disk_free_space disk_total_space diskfreespace disp_e_badindex disp_e_divbyzero disp_e_overflow dl dngettext dns_a dns_a6 dns_aaaa dns_all dns_any dns_check_record dns_cname dns_get_mx dns_get_record dns_hinfo dns_mx dns_naptr dns_ns dns_ptr dns_soa dns_srv dns_txt do dom_hierarchy_request_err dom_import_simplexml dom_index_size_err dom_inuse_attribute_err dom_invalid_access_err dom_invalid_character_err dom_invalid_modification_err dom_invalid_state_err dom_namespace_err dom_no_data_allowed_err dom_no_modification_allowed_err dom_not_found_err
 dom_not_supported_err dom_php_err dom_syntax_err dom_validation_err dom_wrong_document_err domstring_size_err double doubleval e_all e_compile_error e_compile_warning e_core_error e_core_warning e_deprecated e_error e_notice e_parse e_recoverable_error e_strict e_user_deprecated e_user_error e_user_notice e_user_warning e_warning each easter_date easter_days echo eio_busy eio_cancel eio_chmod eio_chown eio_close eio_custom eio_dt_blk eio_dt_chr eio_dt_cmp eio_dt_dir eio_dt_door eio_dt_fifo eio_dt_lnk eio_dt_max eio_dt_mpb eio_dt_mpc eio_dt_nam eio_dt_nwk eio_dt_reg eio_dt_sock eio_dt_unknown eio_dt_wht eio_dup2 eio_event_loop eio_falloc_fl_keep_size eio_fallocate eio_fchmod eio_fchown eio_fdatasync eio_fstat eio_fstatvfs eio_fsync eio_ftruncate eio_futime eio_get_event_stream eio_get_last_error eio_grp eio_grp_add eio_grp_cancel eio_grp_limit eio_init eio_link eio_lstat eio_mkdir eio_mknod eio_nop eio_npending eio_nready eio_nreqs eio_nthreads eio_o_append eio_o_creat eio_o_excl eio_o_fsync eio_o_nonblock eio_o_rdonly eio_o_rdwr eio_o_trunc eio_o_wronly eio_open eio_poll eio_pri_default eio_pri_max eio_pri_min eio_read eio_readahead eio_readdir eio_readdir_dents eio_readdir_dirs_first eio_readdir_found_unknown eio_readdir_stat_order eio_readlink eio_realpath eio_rename eio_rmdir eio_s_ifblk eio_s_ifchr eio_s_ififo eio_s_ifreg eio_s_ifsock eio_s_irgrp eio_s_iroth eio_s_irusr eio_s_iwgrp eio_s_iwoth eio_s_iwusr eio_s_ixgrp eio_s_ixoth eio_s_ixusr eio_seek eio_seek_cur eio_seek_end eio_seek_set eio_sendfile eio_set_max_idle eio_set_max_parallel eio_set_max_poll_reqs eio_set_max_poll_time eio_set_min_parallel eio_stat eio_statvfs eio_symlink eio_sync eio_sync_file_range eio_sync_file_range_wait_after eio_sync_file_range_wait_before eio_sync_file_range_write eio_syncfs eio_truncate eio_unlink eio_utime eio_write else elseif empty enc7bit enc8bit encbase64 encbinary encother encquotedprintable end enddeclare endfor endforeach endif endswitch endwhile ent_compat ent_disallowed ent_html401 ent_html5 ent_ignore ent_noquotes ent_quotes ent_substitute ent_xhtml ent_xml1 era era_d_fmt era_d_t_fmt era_t_fmt era_year ereg ereg_replace eregi eregi_replace error_clear_last error_get_last error_log error_reporting error_trace escapeshellarg escapeshellcmd ev_persist ev_read ev_signal ev_timeout ev_write eval event_add event_base_free event_base_loop event_base_loopbreak event_base_loopexit event_base_new event_base_priority_init event_base_reinit event_base_set event_buffer_base_set event_buffer_disable event_buffer_enable event_buffer_fd_set event_buffer_free event_buffer_new event_buffer_priority_set event_buffer_read event_buffer_set_callback event_buffer_timeout_set event_buffer_watermark_set event_buffer_write event_del event_free event_new event_priority_set event_set event_timer_add event_timer_del event_timer_new event_timer_set evloop_nonblock evloop_once exec exif_imagetype exif_read_data exif_tagname exif_thumbnail exif_use_mbstring exit exp exp_eof exp_exact exp_fullbuffer exp_glob exp_regexp exp_timeout expect_expectl expect_popen explode expm1 extends extension_loaded extr_if_exists extr_overwrite extr_prefix_all extr_prefix_if_exists extr_prefix_invalid extr_prefix_same extr_refs extr_skip extract ezmlm_hash f_dupfd f_getfd f_getfl f_getlk f_getown f_rdlck f_setfl f_setlk f_setlkw f_setown f_unlck f_wrlck false fann_cascadetrain_on_data fann_cascadetrain_on_file fann_clear_scaling_params fann_copy fann_cos fann_cos_symmetric fann_create_from_file fann_create_shortcut fann_create_shortcut_array fann_create_sparse fann_create_sparse_array fann_create_standard fann_create_standard_array fann_create_train fann_create_train_from_callback fann_descale_input fann_descale_output fann_descale_train fann_destroy fann_destroy_train fann_duplicate_train_data fann_e_cant_allocate_mem fann_e_cant_open_config_r fann_e_cant_open_config_w fann_e_cant_open_td_r fann_e_cant_open_td_w fann_e_cant_read_config fann_e_cant_read_connections fann_e_cant_read_neuron fann_e_cant_read_td fann_e_cant_train_activation fann_e_cant_use_activation fann_e_cant_use_train_alg fann_e_index_out_of_bound fann_e_input_no_match fann_e_no_error fann_e_output_no_match fann_e_scale_not_present fann_e_train_data_mismatch fann_e_train_data_subset fann_e_wrong_config_version fann_e_wrong_num_connections fann_elliot fann_elliot_symmetric fann_errorfunc_linear fann_errorfunc_tanh fann_gaussian fann_gaussian_stepwise fann_gaussian_symmetric fann_get_activation_function fann_get_activation_steepness fann_get_bias_array fann_get_bit_fail fann_get_bit_fail_limit fann_get_cascade_activation_functions fann_get_cascade_activation_functions_count fann_get_cascade_activation_steepnesses fann_get_cascade_activation_steepnesses_count fann_get_cascade_candidate_change_fraction fann_get_cascade_candidate_limit fann_get_cascade_candidate_stagnation_epochs fann_get_cascade_max_cand_epochs fann_get_cascade_max_out_epochs fann_get_cascade_min_cand_epochs fann_get_cascade_min_out_epochs fann_get_cascade_num_candidate_groups fann_get_cascade_num_candidates fann_get_cascade_output_change_fraction fann_get_cascade_output_stagnation_epochs fann_get_cascade_weight_multiplier fann_get_connection_array fann_get_connection_rate fann_get_errno fann_get_errstr fann_get_layer_array fann_get_learning_momentum fann_get_learning_rate fann_get_mse fann_get_network_type fann_get_num_input fann_get_num_layers fann_get_num_output fann_get_quickprop_decay fann_get_quickprop_mu fann_get_rprop_decrease_factor fann_get_rprop_delta_max fann_get_rprop_delta_min fann_get_rprop_delta_zero fann_get_rprop_increase_factor fann_get_sarprop_step_error_shift fann_get_sarprop_step_error_threshold_factor fann_get_sarprop_temperature fann_get_sarprop_weight_decay_shift fann_get_total_connections fann_get_total_neurons fann_get_train_error_function fann_get_train_stop_function fann_get_training_algorithm fann_init_weights fann_length_train_data fann_linear fann_linear_piece fann_linear_piece_symmetric fann_merge_train_data fann_nettype_layer fann_nettype_shortcut fann_num_input_train_data fann_num_output_train_data fann_print_error fann_randomize_weights fann_read_train_from_file fann_reset_errno fann_reset_errstr fann_reset_mse fann_run fann_save fann_save_train fann_scale_input fann_scale_input_train_data fann_scale_output fann_scale_output_train_data fann_scale_train fann_scale_train_data fann_set_activation_function fann_set_activation_function_hidden fann_set_activation_function_layer fann_set_activation_function_output fann_set_activation_steepness fann_set_activation_steepness_hidden fann_set_activation_steepness_layer fann_set_activation_steepness_output fann_set_bit_fail_limit fann_set_callback fann_set_cascade_activation_functions fann_set_cascade_activation_steepnesses fann_set_cascade_candidate_change_fraction fann_set_cascade_candidate_limit fann_set_cascade_candidate_stagnation_epochs fann_set_cascade_max_cand_epochs fann_set_cascade_max_out_epochs fann_set_cascade_min_cand_epochs fann_set_cascade_min_out_epochs fann_set_cascade_num_candidate_groups fann_set_cascade_output_change_fraction fann_set_cascade_output_stagnation_epochs fann_set_cascade_weight_multiplier fann_set_error_log fann_set_input_scaling_params fann_set_learning_momentum fann_set_learning_rate fann_set_output_scaling_params fann_set_quickprop_decay fann_set_quickprop_mu fann_set_rprop_decrease_factor fann_set_rprop_delta_max fann_set_rprop_delta_min fann_set_rprop_delta_zero fann_set_rprop_increase_factor fann_set_sarprop_step_error_shift fann_set_sarprop_step_error_threshold_factor fann_set_sarprop_temperature fann_set_sarprop_weight_decay_shift fann_set_scaling_params fann_set_train_error_function fann_set_train_stop_function fann_set_training_algorithm fann_set_weight fann_set_weight_array fann_shuffle_train_data fann_sigmoid fann_sigmoid_stepwise fann_sigmoid_symmetric fann_sigmoid_symmetric_stepwise fann_sin fann_sin_symmetric fann_stopfunc_bit fann_stopfunc_mse fann_subset_train_data fann_test fann_test_data fann_threshold fann_threshold_symmetric fann_train fann_train_batch fann_train_epoch fann_train_incremental fann_train_on_data fann_train_on_file fann_train_quickprop fann_train_rprop fann_train_sarprop fastcgi_finish_request fbsql_affected_rows fbsql_assoc fbsql_autocommit fbsql_blob_size fbsql_both fbsql_change_user fbsql_clob_size fbsql_close fbsql_commit fbsql_connect fbsql_create_blob fbsql_create_clob fbsql_create_db fbsql_data_seek fbsql_database fbsql_database_password fbsql_db_query fbsql_db_status fbsql_drop_db fbsql_errno fbsql_error fbsql_fetch_array fbsql_fetch_assoc fbsql_fetch_field fbsql_fetch_lengths fbsql_fetch_object fbsql_fetch_row fbsql_field_flags fbsql_field_len fbsql_field_name fbsql_field_seek fbsql_field_table fbsql_field_type fbsql_free_result fbsql_get_autostart_info fbsql_hostname fbsql_insert_id fbsql_iso_read_committed fbsql_iso_read_uncommitted fbsql_iso_repeatable_read fbsql_iso_serializable fbsql_iso_versioned fbsql_list_dbs fbsql_list_fields fbsql_list_tables fbsql_lob_direct fbsql_lob_handle fbsql_lock_deferred fbsql_lock_optimistic fbsql_lock_pessimistic fbsql_next_result fbsql_noexec fbsql_num fbsql_num_fields fbsql_num_rows fbsql_password fbsql_pconnect fbsql_query fbsql_read_blob fbsql_read_clob fbsql_result fbsql_rollback fbsql_rows_fetched fbsql_running fbsql_select_db fbsql_set_characterset fbsql_set_lob_mode fbsql_set_password fbsql_set_transaction fbsql_start_db fbsql_starting fbsql_stop_db fbsql_stopped fbsql_stopping fbsql_table_name fbsql_tablename fbsql_unknown fbsql_username fbsql_warnings fclose fdf_add_doc_javascript fdf_add_template fdf_close fdf_create fdf_enum_values fdf_errno fdf_error fdf_get_ap fdf_get_attachment fdf_get_encoding fdf_get_file fdf_get_flags fdf_get_opt
 fdf_get_status fdf_get_value fdf_get_version fdf_header fdf_next_field_name fdf_open fdf_open_string fdf_remove_item fdf_save fdf_save_string fdf_set_ap fdf_set_encoding fdf_set_file fdf_set_flags fdf_set_javascript_action fdf_set_on_import_javascript fdf_set_opt fdf_set_status fdf_set_submit_form_action fdf_set_target_frame fdf_set_value fdf_set_version fdfaa fdfaction fdfap fdfapref fdfas fdfcalculate fdfclearff fdfclrf fdfdown fdfdownap fdfenter fdfexit fdfff fdffile fdfflags fdfformat fdfid fdfif fdfkeystroke fdfnormalap fdfrolloverap fdfsetf fdfsetff fdfstatus fdfup fdfvalidate fdfvalue feof fflush fgetc fgetcsv fgets fgetss file file_append file_binary file_exists file_get_contents file_ignore_new_lines file_no_default_context file_put_contents file_skip_empty_lines file_text file_use_include_path fileatime filectime filegroup fileinfo_continue fileinfo_devices fileinfo_mime fileinfo_mime_encoding fileinfo_mime_type fileinfo_none fileinfo_preserve_atime fileinfo_raw fileinfo_symlink fileinode filemtime fileowner fileperms filepro filepro_fieldcount filepro_fieldname filepro_fieldtype filepro_fieldwidth filepro_retrieve filepro_rowcount filesize filetype filter_callback filter_default filter_flag_allow_fraction filter_flag_allow_hex filter_flag_allow_octal filter_flag_allow_scientific filter_flag_allow_thousand filter_flag_empty_string_null filter_flag_encode_amp filter_flag_encode_high filter_flag_encode_low filter_flag_host_required filter_flag_ipv4 filter_flag_ipv6 filter_flag_no_encode_quotes filter_flag_no_priv_range filter_flag_no_res_range filter_flag_none filter_flag_path_required filter_flag_query_required filter_flag_scheme_required filter_flag_strip_backtick filter_flag_strip_high filter_flag_strip_low filter_force_array filter_has_var filter_id filter_input filter_input_array filter_list filter_null_on_failure filter_require_array filter_require_scalar filter_sanitize_email filter_sanitize_encoded filter_sanitize_full_special_chars filter_sanitize_magic_quotes filter_sanitize_number_float filter_sanitize_number_int filter_sanitize_special_chars filter_sanitize_string filter_sanitize_stripped filter_sanitize_url filter_unsafe_raw filter_validate_boolean filter_validate_email filter_validate_float filter_validate_int filter_validate_ip filter_validate_mac filter_validate_regexp filter_validate_url filter_var filter_var_array final finally finfo_buffer finfo_close finfo_file finfo_open finfo_set_flags firebird/interbase float floatval flock floor flush fmod fnm_casefold fnm_noescape fnm_pathname fnm_period fnmatch fopen for force_deflate force_gzip foreach forward_static_call forward_static_call_array fpassthru fpe_fltdiv fpe_fltinv fpe_fltovf fpe_fltres fpe_fltsub fpe_fltund fpe_intdiv fpe_intovf fprintf fputcsv fputs frac_digits fread frenchtojd fscanf fseek fsockopen fstat ft_internal ft_not ft_peek ft_prefetchtext ft_uid ftell ftok ftp_alloc ftp_ascii ftp_autoresume ftp_autoseek ftp_binary ftp_cdup ftp_chdir ftp_chmod ftp_close ftp_connect ftp_delete ftp_exec ftp_failed ftp_fget ftp_finished ftp_fput ftp_get ftp_get_option ftp_image ftp_login ftp_mdtm ftp_mkdir ftp_moredata ftp_nb_continue ftp_nb_fget ftp_nb_fput ftp_nb_get ftp_nb_put ftp_nlist ftp_pasv ftp_put ftp_pwd ftp_quit ftp_raw ftp_rawlist ftp_rename ftp_rmdir ftp_set_option ftp_site ftp_size ftp_ssl_connect ftp_systype ftp_text ftp_timeout_sec ftruncate func_get_arg func_get_args func_num_args function function_exists function_trace fwrite gc_collect_cycles gc_disable gc_enable gc_enabled gd_bundled gd_extra_version gd_info gd_major_version gc_mem_caches gd_minor_version gd_release_version gd_version geoip_asnum_by_name geoip_asnum_edition geoip_cabledsl_speed geoip_city_edition_rev0 geoip_city_edition_rev1 geoip_continent_code_by_name geoip_corporate_speed geoip_country_code3_by_name geoip_country_code_by_name geoip_country_edition geoip_country_name_by_name geoip_database_info geoip_db_avail geoip_db_filename geoip_db_get_all_info geoip_dialup_speed geoip_domain_by_name geoip_domain_edition geoip_id_by_name geoip_isp_by_name geoip_isp_edition geoip_netspeed_edition geoip_netspeedcell_by_name geoip_org_by_name geoip_org_edition geoip_proxy_edition geoip_record_by_name geoip_region_by_name geoip_region_edition_rev0 geoip_region_edition_rev1 geoip_region_name_by_code geoip_setup_custom_directory geoip_time_zone_by_country_and_region geoip_unknown_speed get_browser get_called_class get_cfg_var get_class get_class_methods get_class_vars get_current_user get_declared_classes get_declared_interfaces get_declared_traits get_defined_constants get_defined_functions get_defined_vars get_extension_funcs get_headers get_html_translation_table get_include_path get_included_files get_loaded_extensions get_magic_quotes_gpc get_magic_quotes_runtime get_meta_tags get_object_vars get_parent_class get_required_files get_resource_type get_resources getallheaders getcwd getdate getdir getenv gethostbyaddr gethostbyname gethostbynamel gethostname getimagesize getimagesizefromstring getlastmod getmxrr getmygid getmyinode getmypid getmyuid getopt getprotobyname getprotobynumber getrandmax getrusage getservbyname getservbyport gettext gettimeofday gettype glob glob_available_flags glob_brace glob_err glob_mark glob_nocheck glob_noescape glob_nosort glob_onlydir global globals gmdate gmmktime gmp_abs gmp_add gmp_and gmp_big_endian gmp_clrbit gmp_cmp gmp_com gmp_div gmp_div_q gmp_div_qr gmp_div_r gmp_divexact gmp_export gmp_fact gmp_gcd gmp_gcdext gmp_hamdist gmp_import gmp_init gmp_intval gmp_invert gmp_jacobi gmp_legendre gmp_little_endian gmp_lsw_first gmp_mod gmp_mpir_version gmp_msw_first gmp_mul gmp_native_endian gmp_neg gmp_nextprime gmp_or gmp_perfect_square gmp_popcount gmp_pow gmp_powm gmp_prob_prime gmp_random gmp_random_bits gmp_random_range gmp_random_seed gmp_root gmp_rootrem gmp_round_minusinf gmp_round_plusinf gmp_round_zero gmp_scan0 gmp_scan1 gmp_setbit gmp_sign gmp_sqrt gmp_sqrtrem gmp_strval gmp_sub gmp_testbit gmp_version gmp_xor gmstrftime gnupg_adddecryptkey gnupg_addencryptkey gnupg_addsignkey gnupg_cleardecryptkeys gnupg_clearencryptkeys gnupg_clearsignkeys gnupg_decrypt gnupg_decryptverify gnupg_encrypt gnupg_encryptsign gnupg_error_exception gnupg_error_silent gnupg_error_warning gnupg_export gnupg_geterror gnupg_getprotocol gnupg_import gnupg_init gnupg_keyinfo gnupg_protocol_cms gnupg_protocol_openpgp gnupg_setarmor gnupg_seterrormode gnupg_setsignmode gnupg_sig_mode_clear gnupg_sig_mode_detach gnupg_sig_mode_normal gnupg_sign gnupg_sigsum_bad_policy gnupg_sigsum_crl_missing gnupg_sigsum_crl_too_old gnupg_sigsum_green gnupg_sigsum_key_expired gnupg_sigsum_key_missing gnupg_sigsum_key_revoked gnupg_sigsum_red gnupg_sigsum_sig_expired gnupg_sigsum_sys_error gnupg_sigsum_valid gnupg_validity_full gnupg_validity_marginal gnupg_validity_never gnupg_validity_ultimate gnupg_validity_undefined gnupg_validity_unknown gnupg_verify gopher_binary gopher_binhex gopher_directory gopher_document gopher_dosbinary gopher_http gopher_info gopher_parsedir gopher_unknown gopher_uuencoded goto grapheme_extr_count grapheme_extr_maxbytes grapheme_extr_maxchars grapheme_extract grapheme_stripos grapheme_stristr grapheme_strlen grapheme_strpos grapheme_strripos grapheme_strrpos grapheme_strstr grapheme_substr gregoriantojd grouping gupnp_context_get_host_ip gupnp_context_get_port gupnp_context_get_subscription_timeout gupnp_context_host_path gupnp_context_new gupnp_context_set_subscription_timeout gupnp_context_timeout_add gupnp_context_unhost_path gupnp_control_error_action_failed gupnp_control_error_invalid_action gupnp_control_error_invalid_args gupnp_control_error_out_of_sync gupnp_control_point_browse_start gupnp_control_point_browse_stop gupnp_control_point_callback_set gupnp_control_point_new gupnp_device_action_callback_set gupnp_device_info_get gupnp_device_info_get_service gupnp_root_device_get_available gupnp_root_device_get_relative_location gupnp_root_device_new gupnp_root_device_set_available gupnp_root_device_start gupnp_root_device_stop gupnp_service_action_get gupnp_service_action_return gupnp_service_action_return_error gupnp_service_action_set gupnp_service_freeze_notify gupnp_service_info_get gupnp_service_info_get_introspection gupnp_service_introspection_get_state_variable gupnp_service_notify gupnp_service_proxy_action_get gupnp_service_proxy_action_set gupnp_service_proxy_add_notify gupnp_service_proxy_callback_set gupnp_service_proxy_get_subscribed gupnp_service_proxy_remove_notify gupnp_service_proxy_send_action gupnp_service_proxy_set_subscribed gupnp_service_thaw_notify gupnp_signal_action_invoked gupnp_signal_device_proxy_available gupnp_signal_device_proxy_unavailable gupnp_signal_notify_failed gupnp_signal_service_proxy_available gupnp_signal_service_proxy_unavailable gupnp_signal_subscription_lost gupnp_type_boolean gupnp_type_double gupnp_type_float gupnp_type_int gupnp_type_long gupnp_type_string gzclose gzcompress gzdecode gzdeflate gzencode gzeof gzfile gzgetc gzgets gzgetss gzinflate gzopen gzpassthru gzputs gzread gzrewind gzseek gztell gzuncompress gzwrite hash hash_algos hash_copy hash_equals hash_file hash_final hash_hmac hash_hmac_file hash_init hash_pbkdf2 hash_update hash_update_file hash_update_stream header header_register_callback header_remove headers_list headers_sent hebrev hebrevc hex2bin hexdec highlight_file highlight_string html_entities html_entity_decode html_specialchars htmlentities htmlspecialchars htmlspecialchars_decode http_auth_any http_auth_basic http_auth_digest http_auth_gssneg http_auth_ntlm http_build_cookie http_build_query http_build_str http_build_url http_cache_etag http_cache_last_modified http_chunked_decode http_cookie_httponly http_cookie_parse_raw http_cookie_secure http_date http_deflate http_deflate_level_def
 http_deflate_level_max http_deflate_level_min http_deflate_strategy_def http_deflate_strategy_filt http_deflate_strategy_fixed http_deflate_strategy_huff http_deflate_strategy_rle http_deflate_type_gzip http_deflate_type_raw http_deflate_type_zlib http_e_encoding http_e_header http_e_invalid_param http_e_malformed_headers http_e_message_type http_e_querystring http_e_request http_e_request_method http_e_request_pool http_e_response http_e_runtime http_e_socket http_e_url http_encoding_stream_flush_full http_encoding_stream_flush_none http_encoding_stream_flush_sync http_get http_get_request_body http_get_request_body_stream http_get_request_headers http_head http_inflate http_ipresolve_any http_ipresolve_v4 http_ipresolve_v6 http_match_etag http_match_modified http_match_request_header http_meth_acl http_meth_baseline_control http_meth_checkin http_meth_checkout http_meth_connect http_meth_copy http_meth_delete http_meth_get http_meth_head http_meth_label http_meth_lock http_meth_merge http_meth_mkactivity http_meth_mkcol http_meth_mkworkspace http_meth_move http_meth_options http_meth_post http_meth_propfind http_meth_proppatch http_meth_put http_meth_report http_meth_trace http_meth_uncheckout http_meth_unlock http_meth_update http_meth_version_control http_msg_none http_msg_request http_msg_response http_negotiate_charset http_negotiate_content_type http_negotiate_language http_params_allow_comma http_params_allow_failure http_params_default http_params_raise_error http_parse_cookie http_parse_headers http_parse_message http_parse_params http_persistent_handles_clean http_persistent_handles_count http_persistent_handles_ident http_post_data http_post_fields http_proxy_http http_proxy_socks4 http_proxy_socks5 http_put_data http_put_file http_put_stream http_querystring_type_array http_querystring_type_bool http_querystring_type_float http_querystring_type_int http_querystring_type_object http_querystring_type_string http_redirect http_redirect_found http_redirect_perm http_redirect_post http_redirect_proxy http_redirect_temp http_request http_request_body_encode http_request_method_exists http_request_method_name http_request_method_register http_request_method_unregister http_response_code http_send_content_disposition http_send_content_type http_send_data http_send_file http_send_last_modified http_send_status http_send_stream http_ssl_version_any http_ssl_version_sslv2 http_ssl_version_sslv3 http_ssl_version_tlsv1 http_support http_support_encodings http_support_magicmime http_support_requests http_support_sslrequests http_throttle http_url_join_path http_url_join_query http_url_replace http_url_strip_all http_url_strip_auth http_url_strip_fragment http_url_strip_pass http_url_strip_path http_url_strip_port http_url_strip_query http_url_strip_user http_version_1_0 http_version_1_1 http_version_any hypot ibase_add_user ibase_affected_rows ibase_backup ibase_bkp_convert ibase_bkp_ignore_checksums ibase_bkp_ignore_limbo ibase_bkp_metadata_only ibase_bkp_no_garbage_collect ibase_bkp_non_transportable ibase_bkp_old_descriptions ibase_blob_add ibase_blob_cancel ibase_blob_close ibase_blob_create ibase_blob_echo ibase_blob_get ibase_blob_import ibase_blob_info ibase_blob_open ibase_close ibase_commit ibase_commit_ret ibase_committed ibase_concurrency ibase_connect ibase_consistency ibase_db_info ibase_default ibase_delete_user ibase_drop_db ibase_errcode ibase_errmsg ibase_execute ibase_fetch_arrays ibase_fetch_assoc ibase_fetch_blobs ibase_fetch_object ibase_fetch_row ibase_field_info ibase_free_event_handler ibase_free_query ibase_free_result ibase_gen_id ibase_maintain_db ibase_modify_user ibase_name_result ibase_nowait ibase_num_fields ibase_num_params ibase_param_info ibase_pconnect ibase_prepare ibase_prp_access_mode ibase_prp_activate ibase_prp_am_readonly ibase_prp_am_readwrite ibase_prp_db_online ibase_prp_deny_new_attachments ibase_prp_deny_new_transactions ibase_prp_page_buffers ibase_prp_res ibase_prp_res_use_full ibase_prp_reserve_space ibase_prp_set_sql_dialect ibase_prp_shutdown_db ibase_prp_sweep_interval ibase_prp_wm_async ibase_prp_wm_sync ibase_prp_write_mode ibase_query ibase_read ibase_res_create ibase_res_deactivate_idx ibase_res_no_shadow ibase_res_no_validity ibase_res_one_at_a_time ibase_res_replace ibase_res_use_all_space ibase_restore ibase_rollback ibase_rollback_ret ibase_rpr_check_db ibase_rpr_full ibase_rpr_ignore_checksum ibase_rpr_kill_shadows ibase_rpr_mend_db ibase_rpr_sweep_db ibase_rpr_validate_db ibase_server_info ibase_service_attach ibase_service_detach ibase_set_event_handler ibase_sts_data_pages ibase_sts_db_log ibase_sts_hdr_pages ibase_sts_idx_pages ibase_sts_sys_relations ibase_svc_get_env ibase_svc_get_env_lock ibase_svc_get_env_msg ibase_svc_get_users ibase_svc_implementation ibase_svc_server_version ibase_svc_svr_db_info ibase_svc_user_dbpath ibase_trans ibase_unixtime ibase_wait ibase_wait_event ibase_write iconv iconv_get_encoding iconv_impl iconv_mime_decode iconv_mime_decode_continue_on_error iconv_mime_decode_headers iconv_mime_decode_strict iconv_mime_encode iconv_set_encoding iconv_strlen iconv_strpos iconv_strrpos iconv_substr iconv_version id3_best id3_get_frame_long_name id3_get_frame_short_name id3_get_genre_id id3_get_genre_list id3_get_genre_name id3_get_tag id3_get_version id3_remove_tag id3_set_tag id3_v1_0 id3_v1_1 id3_v2_1 id3_v2_2 id3_v2_3 id3_v2_4 idate idn_to_ascii idn_to_unicode idn_to_utf8 idna_allow_unassigned idna_check_bidi idna_check_contextj idna_default idna_error_bidi idna_error_contextj idna_error_disallowed idna_error_domain_name_too_long idna_error_empty_label idna_error_hyphen_3_4 idna_error_invalid_ace_label idna_error_label_has_dot idna_error_label_too_long idna_error_leading_combining_mark idna_error_leading_hyphen idna_error_punycode idna_error_trailing_hyphen idna_nontransitional_to_ascii idna_nontransitional_to_unicode idna_use_std3_rules if ifx_affected_rows ifx_blobinfile_mode ifx_byteasvarchar ifx_close ifx_connect ifx_copy_blob ifx_create_blob ifx_create_char ifx_do ifx_error ifx_errormsg ifx_fetch_row ifx_fieldproperties ifx_fieldtypes ifx_free_blob ifx_free_char ifx_free_result ifx_get_blob ifx_get_char ifx_getsqlca ifx_hold ifx_htmltbl_result ifx_lo_append ifx_lo_buffer ifx_lo_nobuffer ifx_lo_rdonly ifx_lo_rdwr ifx_lo_wronly ifx_nullformat ifx_num_fields ifx_num_rows ifx_pconnect ifx_prepare ifx_query ifx_scroll ifx_textasvarchar ifx_update_blob ifx_update_char ifxus_close_slob ifxus_create_slob ifxus_free_slob ifxus_open_slob ifxus_read_slob ifxus_seek_slob ifxus_tell_slob ifxus_write_slob ignore_user_abort iis_add_server iis_anonymous iis_basic iis_execute iis_get_dir_security iis_get_script_map iis_get_server_by_comment iis_get_server_by_path iis_get_server_rights iis_get_service_state iis_ntlm iis_paused iis_read iis_remove_server iis_running iis_script iis_set_app_settings iis_set_dir_security iis_set_script_map iis_set_server_rights iis_start_server iis_start_service iis_starting iis_stop_server iis_stop_service iis_stopped iis_write ill_badstk ill_coproc ill_illadr ill_illopc ill_illopn ill_illtrp ill_prvopc ill_prvreg image2wbmp image_type_to_extension image_type_to_mime_type imageaffine imageaffinematrixconcat imageaffinematrixget imagealphablending imageantialias imagearc imagechar imagecharup imagecolorallocate imagecolorallocatealpha imagecolorat imagecolorclosest imagecolorclosestalpha imagecolorclosesthwb imagecolordeallocate imagecolorexact imagecolorexactalpha imagecolormatch imagecolorresolve imagecolorresolvealpha imagecolorset imagecolorsforindex imagecolorstotal imagecolortransparent imageconvolution imagecopy imagecopymerge imagecopymergegray imagecopyresampled imagecopyresized imagecreate imagecreatefromgd imagecreatefromgd2 imagecreatefromgd2part imagecreatefromgif imagecreatefromjpeg imagecreatefrompng imagecreatefromstring imagecreatefromwbmp imagecreatefromwebp imagecreatefromxbm imagecreatefromxpm imagecreatetruecolor imagecrop imagecropauto imagedashedline imagedestroy imageellipse imagefill imagefilledarc imagefilledellipse imagefilledpolygon imagefilledrectangle imagefilltoborder imagefilter imageflip imagefontheight imagefontwidth imageftbbox imagefttext imagegammacorrect imagegd imagegd2 imagegif imagegrabscreen imagegrabwindow imageinterlace imageistruecolor imagejpeg imagelayereffect imageline imageloadfont imagepalettecopy imagepalettetotruecolor imagepng imagepolygon imagepsbbox imagepsencodefont imagepsextendfont imagepsfreefont imagepsloadfont imagepsslantfont imagepstext imagerectangle imagerotate imagesavealpha imagescale imagesetbrush imagesetinterpolation imagesetpixel imagesetstyle imagesetthickness imagesettile imagestring imagestringup imagesx imagesy imagetruecolortopalette imagettfbbox imagettftext imagetype_bmp imagetype_count imagetype_gif imagetype_ico imagetype_iff imagetype_jb2 imagetype_jp2 imagetype_jpc imagetype_jpeg imagetype_jpeg2000 imagetype_jpx imagetype_png imagetype_psd imagetype_swc imagetype_swf imagetype_tiff_ii imagetype_tiff_mm imagetype_unknown imagetype_wbmp imagetype_xbm imagetypes imagewbmp imagewebp imagexbm imap_8bit imap_alerts imap_append imap_base64 imap_binary imap_body imap_bodystruct imap_check imap_clearflag_full imap_close imap_closetimeout imap_create imap_createmailbox imap_delete imap_deletemailbox imap_errors imap_expunge imap_fetch_overview imap_fetchbody imap_fetchheader imap_fetchmime imap_fetchstructure imap_fetchtext imap_gc imap_gc_elt imap_gc_env imap_gc_texts imap_get_quota imap_get_quotaroot imap_getacl imap_getmailboxes imap_getsubscribed imap_header imap_headerinfo imap_headers imap_last_error imap_list imap_listmailbox imap_listscan imap_listsubscribed imap_lsub imap_mail imap_mail_compose imap_mail_copy imap_mail_move
 imap_mailboxmsginfo imap_mime_header_decode imap_msgno imap_mutf7_to_utf8 imap_num_msg imap_num_recent imap_open imap_opentimeout imap_ping imap_qprint imap_readtimeout imap_rename imap_renamemailbox imap_reopen imap_rfc822_parse_adrlist imap_rfc822_parse_headers imap_rfc822_write_address imap_savebody imap_scan imap_scanmailbox imap_search imap_set_quota imap_setacl imap_setflag_full imap_sort imap_status imap_subscribe imap_thread imap_timeout imap_uid imap_undelete imap_unsubscribe imap_utf7_decode imap_utf7_encode imap_utf8 imap_utf8_to_mutf7 imap_writetimeout img_affine_rotate img_affine_scale img_affine_shear_horizontal img_affine_shear_vertical img_affine_translate img_arc_chord img_arc_edged img_arc_nofill img_arc_pie img_arc_rounded img_bell img_bessel img_bicubic img_bicubic_fixed img_bilinear_fixed img_blackman img_box img_bspline img_catmullrom img_color_brushed img_color_styled img_color_styledbrushed img_color_tiled img_color_transparent img_crop_black img_crop_default img_crop_sides img_crop_threshold img_crop_transparent img_crop_white img_effect_alphablend img_effect_normal img_effect_overlay img_effect_replace img_filter_brightness img_filter_colorize img_filter_contrast img_filter_edgedetect img_filter_emboss img_filter_gaussian_blur img_filter_grayscale img_filter_mean_removal img_filter_negate img_filter_pixelate img_filter_selective_blur img_filter_smooth img_flip_both img_flip_horizontal img_flip_vertical img_gaussian img_gd2_compressed img_gd2_raw img_generalized_cubic img_gif img_hamming img_hanning img_hermite img_jpeg img_jpg img_mitchell img_nearest_neighbour img_png img_power img_quadratic img_sinc img_triangle img_wbmp img_weighted4 img_xpm implements implode import_request_variables in_access in_all_events in_array in_attrib in_close in_close_nowrite in_close_write in_create in_delete in_delete_self in_dont_follow in_ignored in_isdir in_mask_add in_modify in_move in_move_self in_moved_from in_moved_to in_oneshot in_onlydir in_open in_q_overflow in_unmount include include_once inet_ntop inet_pton inf info_all info_configuration info_credits info_environment info_general info_license info_modules info_variables ingres_api_version ingres_assoc ingres_autocommit ingres_autocommit_state ingres_both ingres_charset ingres_close ingres_commit ingres_connect ingres_cursor ingres_cursor_readonly ingres_cursor_update ingres_date_dmy ingres_date_finnish ingres_date_german ingres_date_iso ingres_date_iso4 ingres_date_mdy ingres_date_multinational ingres_date_multinational4 ingres_date_ymd ingres_errno ingres_error ingres_errsqlstate ingres_escape_string ingres_execute ingres_ext_version ingres_fetch_array ingres_fetch_assoc ingres_fetch_object ingres_fetch_proc_return ingres_fetch_row ingres_field_length ingres_field_name ingres_field_nullable ingres_field_precision ingres_field_scale ingres_field_type ingres_free_result ingres_money_leading ingres_money_trailing ingres_next_error ingres_num ingres_num_fields ingres_num_rows ingres_pconnect ingres_prepare ingres_query ingres_result_seek ingres_rollback ingres_set_environment ingres_structure_btree ingres_structure_cbtree ingres_structure_chash ingres_structure_cheap ingres_structure_cisam ingres_structure_hash ingres_structure_heap ingres_structure_isam ingres_unbuffered_query ini_all ini_alter ini_get ini_get_all ini_perdir ini_restore ini_scanner_normal ini_scanner_raw ini_scanner_typed ini_set ini_system ini_user inotify_add_watch inotify_init inotify_queue_len inotify_read inotify_rm_watch input_cookie input_env input_get input_post input_request input_server input_session instanceof insteadof int int_curr_symbol int_frac_digits intdiv integer interface interface_exists intl_error_name intl_get_error_code intl_get_error_message intl_icu_data_version intl_icu_version intl_idna_variant_2003 intl_idna_variant_uts46 intl_is_failure intl_max_locale_len intval ion_clock_skew ion_corrupt_file ion_expired_file ion_license_corrupt ion_license_expired ion_license_header_invalid ion_license_not_found ion_license_property_invalid ion_license_server_invalid ion_no_permissions ion_unauth_append_prepend_file ion_unauth_included_file ion_unauth_including_file ion_untrusted_extension ioncube_check_license_properties ioncube_file_info ioncube_file_is_encoded ioncube_file_not_permissioned ioncube_file_properties ioncube_license_has_expired ioncube_license_matches_server ioncube_license_properties ioncube_licensed_servers ioncube_loader_iversion ioncube_loader_version ioncube_read_file ioncube_server_data ioncube_write_file ip2long ip_multicast_if ip_multicast_loop ip_multicast_ttl ipproto_ip ipproto_ipv6 iptcembed iptcparse ipv6_hoplimit ipv6_multicast_hops ipv6_multicast_if ipv6_multicast_loop ipv6_pktinfo ipv6_recvhoplimit ipv6_recvpktinfo ipv6_recvtclass ipv6_tclass ipv6_unicast_hops is_a is_array is_bool is_callable is_dir is_double is_executable is_file is_finite is_float is_infinite is_int is_integer is_link is_long is_nan is_null is_numeric is_object is_readable is_real is_resource is_scalar is_soap_fault is_string is_subclass_of is_tainted is_uploaded_file is_writable is_writeable isset iterator_apply iterator_count iterator_to_array jddayofweek jdmonthname jdtofrench jdtogregorian jdtojewish jdtojulian jdtounix jewishtojd join jpeg2wbmp json_bigint_as_string json_decode json_encode json_error_ctrl_char json_error_depth json_error_inf_or_nan json_error_none json_error_recursion json_error_state_mismatch json_error_syntax json_error_unsupported_type json_error_utf8 json_force_object json_hex_amp json_hex_apos json_hex_quot json_hex_tag json_last_error json_last_error_msg json_numeric_check json_object_as_array json_partial_output_on_error json_preserve_zero_fraction json_pretty_print json_unescaped_slashes json_unescaped_unicode judy_type judy_version juliantojd kadm5_attributes kadm5_chpass_principal kadm5_clearpolicy kadm5_create_principal kadm5_delete_principal kadm5_destroy kadm5_fail_auth_count kadm5_flush kadm5_get_policies kadm5_get_principal kadm5_get_principals kadm5_init_with_password kadm5_kvno kadm5_last_failed kadm5_last_pw_change kadm5_last_success kadm5_max_life kadm5_max_rlife kadm5_mod_name kadm5_mod_time kadm5_modify_principal kadm5_policy kadm5_princ_expire_time kadm5_principal kadm5_pw_expiration kadm5_randkey key key_exists krb5_kdb_disallow_all_tix krb5_kdb_disallow_dup_skey krb5_kdb_disallow_forwardable krb5_kdb_disallow_postdated krb5_kdb_disallow_proxiable krb5_kdb_disallow_renewable krb5_kdb_disallow_svr krb5_kdb_disallow_tgt_based krb5_kdb_new_princ krb5_kdb_pwchange_server krb5_kdb_requires_hw_auth krb5_kdb_requires_pre_auth krb5_kdb_requires_pwchange krb5_kdb_support_desmd5 krsort ksort latt_haschildren latt_hasnochildren latt_marked latt_noinferiors latt_noselect latt_referral latt_unmarked lc_all lc_collate lc_ctype lc_messages lc_monetary lc_numeric lc_time lcfirst lcg_value lchgrp lchown ldap_8859_to_t61 ldap_add ldap_bind ldap_close ldap_compare ldap_connect ldap_control_paged_result ldap_control_paged_result_response ldap_count_entries ldap_delete ldap_dn2ufn ldap_err2str ldap_errno ldap_error ldap_escape ldap_explode_dn ldap_first_attribute ldap_first_entry ldap_first_reference ldap_free_result ldap_get_attributes ldap_get_dn ldap_get_entries ldap_get_option ldap_get_values ldap_get_values_len ldap_list ldap_mod_add ldap_mod_del ldap_mod_replace ldap_modify ldap_modify_batch ldap_next_attribute ldap_next_entry ldap_next_reference ldap_parse_reference ldap_parse_result ldap_read ldap_rename ldap_sasl_bind ldap_search ldap_set_option ldap_set_rebind_proc ldap_sort ldap_start_tls ldap_t61_to_8859 ldap_unbind levenshtein libexslt_dotted_version libexslt_version libxml_clear_errors libxml_compact libxml_disable_entity_loader libxml_dotted_version libxml_dtdattr libxml_dtdload libxml_dtdvalid libxml_err_error libxml_err_fatal libxml_err_none libxml_err_warning libxml_get_errors libxml_get_last_error libxml_html_nodefdtd libxml_html_noimplied libxml_loaded_version libxml_noblanks libxml_nocdata libxml_noemptytag libxml_noent libxml_noerror libxml_nonet libxml_nowarning libxml_noxmldecl libxml_nsclean libxml_parsehuge libxml_pedantic libxml_schema_create libxml_set_external_entity_loader libxml_set_streams_context libxml_use_internal_errors libxml_version libxml_xinclude libxslt_dotted_version libxslt_version link linkinfo list locale_accept_from_http locale_canonicalize locale_compose locale_filter_matches locale_get_all_variants locale_get_default locale_get_display_language locale_get_display_name locale_get_display_region locale_get_display_script locale_get_display_variant locale_get_keywords locale_get_primary_language locale_get_region locale_get_script locale_lookup locale_parse locale_set_default localeconv localtime lock_ex lock_nb lock_sh lock_un log log10 log1p log_alert log_auth log_authpriv log_cons log_crit log_cron log_daemon log_debug log_emerg log_err log_info log_kern log_local0 log_local1 log_local2 log_local3 log_local4 log_local5 log_local6 log_local7 log_lpr log_mail log_ndelay log_news log_notice log_nowait log_odelay log_perror log_pid log_syslog log_user log_uucp log_warning long2ip lstat ltrim lzf_compress lzf_decompress lzf_optimized_for m_1_pi m_2_pi m_2_sqrtpi m_checkstatus m_completeauthorizations m_connect m_connectionerror m_deletetrans m_destroyconn m_destroyengine m_done m_e m_error m_euler m_fail m_getcell m_getcellbynum m_getcommadelimited m_getheader m_initconn m_initengine m_iscommadelimited m_ln10 m_ln2 m_lnpi m_log10e m_log2e m_maxconntimeout m_monitor m_numcolumns m_numrows m_parsecommadelimited m_pending m_pi m_pi_2 m_pi_4 m_responsekeys m_responseparam m_returnstatus m_setblocking m_setdropfile m_setip m_setssl m_setssl_cafile m_setssl_files m_settimeout m_sqrt1_2 m_sqrt2
 m_sqrt3 m_sqrtpi m_sslcert_gen_hash m_success m_transactionssent m_transinqueue m_transkeyval m_transnew m_transsend m_uwait m_validateidentifier m_verifyconnection m_verifysslcert magic_quotes_runtime mail mailparse_determine_best_xfer_encoding mailparse_extract_output mailparse_extract_return mailparse_extract_stream mailparse_msg_create mailparse_msg_extract_part mailparse_msg_extract_part_file mailparse_msg_extract_whole_part_file mailparse_msg_free mailparse_msg_get_part mailparse_msg_get_part_data mailparse_msg_get_structure mailparse_msg_parse mailparse_msg_parse_file mailparse_rfc822_parse_addresses mailparse_stream_encode mailparse_uudecode_all main max maxdb_affected_rows maxdb_application maxdb_appversion maxdb_assoc maxdb_assoc_lower maxdb_assoc_upper maxdb_autocommit maxdb_bind_param maxdb_bind_result maxdb_both maxdb_change_user maxdb_character_set_name maxdb_client_encoding maxdb_close maxdb_close_long_data maxdb_commit maxdb_compname maxdb_connect maxdb_connect_errno maxdb_connect_error maxdb_cursorprefix maxdb_data_seek maxdb_debug maxdb_disable_reads_from_master maxdb_disable_rpl_parse maxdb_dump_debug_info maxdb_embedded_connect maxdb_enable_reads_from_master maxdb_enable_rpl_parse maxdb_errno maxdb_error maxdb_escape_string maxdb_execute maxdb_fetch maxdb_fetch_array maxdb_fetch_assoc maxdb_fetch_field maxdb_fetch_field_direct maxdb_fetch_fields maxdb_fetch_lengths maxdb_fetch_object maxdb_fetch_row maxdb_field_count maxdb_field_seek maxdb_field_tell maxdb_free_result maxdb_get_client_info maxdb_get_client_version maxdb_get_host_info maxdb_get_metadata maxdb_get_proto_info maxdb_get_server_info maxdb_get_server_version maxdb_info maxdb_init maxdb_insert_id maxdb_isolationlevel maxdb_kill maxdb_master_query maxdb_more_results maxdb_multi_query maxdb_next_result maxdb_num maxdb_num_fields maxdb_num_rows maxdb_options maxdb_packetcount maxdb_param_count maxdb_ping maxdb_prepare maxdb_query maxdb_real_connect maxdb_real_escape_string maxdb_real_query maxdb_report maxdb_rollback maxdb_rpl_parse_enabled maxdb_rpl_probe maxdb_rpl_query_type maxdb_select_db maxdb_send_long_data maxdb_send_query maxdb_server_end maxdb_server_init maxdb_set_opt maxdb_sqlmode maxdb_sqlstate maxdb_ssl_set maxdb_stat maxdb_statementcachesize maxdb_stmt_affected_rows maxdb_stmt_bind_param maxdb_stmt_bind_result maxdb_stmt_close maxdb_stmt_close_long_data maxdb_stmt_data_seek maxdb_stmt_errno maxdb_stmt_error maxdb_stmt_execute maxdb_stmt_fetch maxdb_stmt_free_result maxdb_stmt_init maxdb_stmt_num_rows maxdb_stmt_param_count maxdb_stmt_prepare maxdb_stmt_reset maxdb_stmt_result_metadata maxdb_stmt_send_long_data maxdb_stmt_sqlstate maxdb_stmt_store_result maxdb_store_result maxdb_thread_id maxdb_thread_safe maxdb_timeout maxdb_unicode maxdb_use_result maxdb_warning_count mb_case_lower mb_case_title mb_case_upper mb_check_encoding mb_convert_case mb_convert_encoding mb_convert_kana mb_convert_variables mb_decode_mimeheader mb_decode_numericentity mb_detect_encoding mb_detect_order mb_encode_mimeheader mb_encode_numericentity mb_encoding_aliases mb_ereg mb_ereg_match mb_ereg_replace mb_ereg_replace_callback mb_ereg_search mb_ereg_search_getpos mb_ereg_search_getregs mb_ereg_search_init mb_ereg_search_pos mb_ereg_search_regs mb_ereg_search_setpos mb_eregi mb_eregi_replace mb_get_info mb_http_input mb_http_output mb_internal_encoding mb_language mb_list_encodings mb_output_handler mb_overload_mail mb_overload_regex mb_overload_string mb_parse_str mb_preferred_mime_name mb_regex_encoding mb_regex_set_options mb_send_mail mb_split mb_strcut mb_strimwidth mb_stripos mb_stristr mb_strlen mb_strpos mb_strrchr mb_strrichr mb_strripos mb_strrpos mb_strstr mb_strtolower mb_strtoupper mb_strwidth mb_substitute_character mb_substr mb_substr_count mbereg mbereg_match mbereg_replace mbereg_search mbereg_search_getpos mbereg_search_getregs mbereg_search_init mbereg_search_pos mbereg_search_regs mbereg_search_setpos mberegi mberegi_replace mbregex_encoding mbsplit mcast_block_source mcast_join_group mcast_join_source_group mcast_leave_group mcast_leave_source_group mcast_unblock_source mcrypt_3des mcrypt_arcfour mcrypt_arcfour_iv mcrypt_blowfish mcrypt_blowfish_compat mcrypt_cast_128 mcrypt_cast_256 mcrypt_cbc mcrypt_cfb mcrypt_create_iv mcrypt_crypt mcrypt_decrypt mcrypt_des mcrypt_dev_random mcrypt_dev_urandom mcrypt_ecb mcrypt_enc_get_algorithms_name mcrypt_enc_get_block_size mcrypt_enc_get_iv_size mcrypt_enc_get_key_size mcrypt_enc_get_modes_name mcrypt_enc_get_supported_key_sizes mcrypt_enc_is_block_algorithm mcrypt_enc_is_block_algorithm_mode mcrypt_enc_is_block_mode mcrypt_enc_self_test mcrypt_encrypt mcrypt_enigna mcrypt_generic mcrypt_generic_deinit mcrypt_generic_end mcrypt_generic_init mcrypt_get_block_size mcrypt_get_cipher_name mcrypt_get_iv_size mcrypt_get_key_size mcrypt_gost mcrypt_idea mcrypt_list_algorithms mcrypt_list_modes mcrypt_loki97 mcrypt_mars mcrypt_mode_cbc mcrypt_mode_cfb mcrypt_mode_ecb mcrypt_mode_nofb mcrypt_mode_ofb mcrypt_mode_stream mcrypt_module_close mcrypt_module_get_algo_block_size mcrypt_module_get_algo_key_size mcrypt_module_get_supported_key_sizes mcrypt_module_is_block_algorithm mcrypt_module_is_block_algorithm_mode mcrypt_module_is_block_mode mcrypt_module_open mcrypt_module_self_test mcrypt_ofb mcrypt_panama mcrypt_rand mcrypt_rc2 mcrypt_rc6 mcrypt_rijndael_128 mcrypt_rijndael_192 mcrypt_rijndael_256 mcrypt_safer128 mcrypt_safer64 mcrypt_saferplus mcrypt_serpent mcrypt_skipjack mcrypt_threeway mcrypt_tripledes mcrypt_twofish mcrypt_wake mcrypt_xtea md5 md5_file mdecrypt_generic memcache_add memcache_add_server memcache_append memcache_cas memcache_close memcache_compressed memcache_connect memcache_debug memcache_decrement memcache_delete memcache_flush memcache_get memcache_get_extended_stats memcache_get_server_status memcache_get_stats memcache_get_version memcache_have_session memcache_increment memcache_pconnect memcache_prepend memcache_replace memcache_set memcache_set_compress_threshold memcache_set_failure_callback memcache_set_server_params memory_get_peak_usage memory_get_usage memory_trace metaphone method_exists mhash mhash_adler32 mhash_count mhash_crc32 mhash_crc32b mhash_fnv132 mhash_fnv164 mhash_fnv1a32 mhash_fnv1a64 mhash_get_block_size mhash_get_hash_name mhash_gost mhash_haval128 mhash_haval160 mhash_haval192 mhash_haval224 mhash_haval256 mhash_joaat mhash_keygen_s2k mhash_md2 mhash_md4 mhash_md5 mhash_ripemd128 mhash_ripemd160 mhash_ripemd256 mhash_ripemd320 mhash_sha1 mhash_sha224 mhash_sha256 mhash_sha384 mhash_sha512 mhash_snefru256 mhash_tiger mhash_tiger128 mhash_tiger160 mhash_whirlpool microtime mime_content_type min ming_keypress ming_new ming_setcubicthreshold ming_setscale ming_setswfcompression ming_useconstants ming_useswfversion ming_zlib mk_e_unavailable mkdir mktime mon_1 mon_10 mon_11 mon_12 mon_2 mon_3 mon_4 mon_5 mon_6 mon_7 mon_8 mon_9 mon_decimal_point mon_grouping mon_thousands_sep money_format mongo_stream_notify_io_completed mongo_stream_notify_io_progress mongo_stream_notify_io_read mongo_stream_notify_io_write mongo_stream_notify_log_batchinsert mongo_stream_notify_log_cmd_delete mongo_stream_notify_log_cmd_insert mongo_stream_notify_log_cmd_update mongo_stream_notify_log_delete mongo_stream_notify_log_getmore mongo_stream_notify_log_insert mongo_stream_notify_log_killcursor mongo_stream_notify_log_query mongo_stream_notify_log_response_header mongo_stream_notify_log_update mongo_stream_notify_log_write_batch mongo_stream_notify_log_write_reply mongo_stream_notify_type_io_init mongo_stream_notify_type_log mongo_streams mongo_supports_auth_mechanism_gssapi mongo_supports_auth_mechanism_mongodb_cr mongo_supports_auth_mechanism_mongodb_x509 mongo_supports_auth_mechanism_plain mongo_supports_ssl mongo_supports_streams move_uploaded_file mqseries_back mqseries_begin mqseries_close mqseries_cmit mqseries_conn mqseries_connx mqseries_disc mqseries_get mqseries_inq mqseries_mqcc_failed mqseries_mqcc_ok mqseries_mqcc_unknown mqseries_mqcc_warning mqseries_open mqseries_put mqseries_put1 mqseries_set mqseries_strerror msession_connect msession_count msession_create msession_destroy msession_disconnect msession_find msession_get msession_get_array msession_get_data msession_inc msession_list msession_listvar msession_lock msession_plugin msession_randstr msession_set msession_set_array msession_set_data msession_timeout msession_uniq msession_unlock msg_ctrunc msg_dontroute msg_dontwait msg_eagain msg_enomsg msg_eof msg_eor msg_except msg_get_queue msg_ipc_nowait msg_noerror msg_oob msg_peek msg_queue_exists msg_receive msg_remove_queue msg_send msg_set_queue msg_stat_queue msg_trunc msg_waitall msgfmt_create msgfmt_format msgfmt_format_message msgfmt_get_error_code msgfmt_get_error_message msgfmt_get_locale msgfmt_get_pattern msgfmt_parse msgfmt_parse_message msgfmt_set_pattern msql msql_affected_rows msql_assoc msql_both msql_close msql_connect msql_create_db msql_createdb msql_data_seek msql_db_query msql_dbname msql_drop_db msql_error msql_fetch_array msql_fetch_field msql_fetch_object msql_fetch_row msql_field_flags msql_field_len msql_field_name msql_field_seek msql_field_table msql_field_type msql_fieldflags msql_fieldlen msql_fieldname msql_fieldtable msql_fieldtype msql_free_result msql_list_dbs msql_list_fields msql_list_tables msql_num msql_num_fields msql_num_rows msql_numfields msql_numrows msql_pconnect msql_query msql_regcase msql_result msql_select_db msql_tablename mssql_assoc mssql_bind mssql_both mssql_close mssql_connect mssql_data_seek mssql_execute mssql_fetch_array mssql_fetch_assoc mssql_fetch_batch mssql_fetch_field mssql_fetch_object mssql_fetch_row mssql_field_length mssql_field_name mssql_field_seek mssql_field_type mssql_free_result
 mssql_free_statement mssql_get_last_message mssql_guid_string mssql_init mssql_min_error_severity mssql_min_message_severity mssql_next_result mssql_num mssql_num_fields mssql_num_rows mssql_pconnect mssql_query mssql_result mssql_rows_affected mssql_select_db mt_getrandmax mt_rand mt_srand mysql mysql_affected_rows mysql_assoc mysql_both mysql_client_compress mysql_client_encoding mysql_client_ignore_space mysql_client_interactive mysql_client_ssl mysql_close mysql_connect mysql_create_db mysql_data_seek mysql_db_name mysql_db_query mysql_dbname mysql_drop_db mysql_errno mysql_error mysql_escape_string mysql_fetch_array mysql_fetch_assoc mysql_fetch_field mysql_fetch_lengths mysql_fetch_object mysql_fetch_row mysql_field_flags mysql_field_len mysql_field_name mysql_field_seek mysql_field_table mysql_field_type mysql_fieldflags mysql_fieldlen mysql_fieldname mysql_fieldtable mysql_fieldtype mysql_free_result mysql_freeresult mysql_get_client_info mysql_get_host_info mysql_get_proto_info mysql_get_server_info mysql_info mysql_insert_id mysql_list_dbs mysql_list_fields mysql_list_processes mysql_list_tables mysql_listdbs mysql_listfields mysql_listtables mysql_num mysql_num_fields mysql_num_rows mysql_numfields mysql_numrows mysql_pconnect mysql_ping mysql_query mysql_real_escape_string mysql_result mysql_select_db mysql_selectdb mysql_set_charset mysql_stat mysql_table_name mysql_tablename mysql_thread_id mysql_unbuffered_query mysqli_affected_rows mysqli_assoc mysqli_async mysqli_auto_increment_flag mysqli_autocommit mysqli_begin_transaction mysqli_binary_flag mysqli_bind_param mysqli_bind_result mysqli_blob_flag mysqli_both mysqli_change_user mysqli_character_set_name mysqli_client_can_handle_expired_passwords mysqli_client_compress mysqli_client_encoding mysqli_client_found_rows mysqli_client_ignore_space mysqli_client_interactive mysqli_client_multi_queries mysqli_client_no_schema mysqli_client_ssl mysqli_close mysqli_commit mysqli_connect mysqli_connect_errno mysqli_connect_error mysqli_cursor_type_for_update mysqli_cursor_type_no_cursor mysqli_cursor_type_read_only mysqli_cursor_type_scrollable mysqli_data_seek mysqli_data_truncated mysqli_debug mysqli_debug_trace_enabled mysqli_dump_debug_info mysqli_embedded_server_end mysqli_embedded_server_start mysqli_enum_flag mysqli_errno mysqli_error mysqli_error_list mysqli_escape_string mysqli_execute mysqli_fetch mysqli_fetch_all mysqli_fetch_array mysqli_fetch_assoc mysqli_fetch_field mysqli_fetch_field_direct mysqli_fetch_fields mysqli_fetch_lengths mysqli_fetch_object mysqli_fetch_row mysqli_field_count mysqli_field_seek mysqli_field_tell mysqli_free_result mysqli_get_cache_stats mysqli_get_charset mysqli_get_client_info mysqli_get_client_stats mysqli_get_client_version mysqli_get_connection_stats mysqli_get_host_info mysqli_get_links_stats mysqli_get_metadata mysqli_get_proto_info mysqli_get_server_info mysqli_get_server_version mysqli_get_warnings mysqli_group_flag mysqli_info mysqli_init mysqli_init_command mysqli_insert_id mysqli_kill mysqli_more_results mysqli_multi_query mysqli_multiple_key_flag mysqli_need_data mysqli_next_result mysqli_no_data mysqli_no_default_value_flag mysqli_not_null_flag mysqli_num mysqli_num_fields mysqli_num_flag mysqli_num_rows mysqli_on_update_now_flag mysqli_opt_can_handle_expired_passwords mysqli_opt_connect_timeout mysqli_opt_int_and_float_native mysqli_opt_local_infile mysqli_opt_net_cmd_buffer_size mysqli_opt_net_read_buffer_size mysqli_opt_ssl_verify_server_cert mysqli_options mysqli_param_count mysqli_part_key_flag mysqli_ping mysqli_poll mysqli_prepare mysqli_pri_key_flag mysqli_query mysqli_read_default_file mysqli_read_default_group mysqli_real_connect mysqli_real_escape_string mysqli_real_query mysqli_reap_async_query mysqli_refresh mysqli_refresh_backup_log mysqli_refresh_grant mysqli_refresh_hosts mysqli_refresh_log mysqli_refresh_master mysqli_refresh_slave mysqli_refresh_status mysqli_refresh_tables mysqli_refresh_threads mysqli_release_savepoint mysqli_report mysqli_report_all mysqli_report_error mysqli_report_index mysqli_report_off mysqli_report_strict mysqli_rollback mysqli_savepoint mysqli_select_db mysqli_send_long_data mysqli_server_ps_out_params mysqli_server_public_key mysqli_server_query_no_good_index_used mysqli_server_query_no_index_used mysqli_server_query_was_slow mysqli_set_charset mysqli_set_charset_dir mysqli_set_charset_name mysqli_set_flag mysqli_set_local_infile_default mysqli_set_local_infile_handler mysqli_set_opt mysqli_sqlstate mysqli_ssl_set mysqli_stat mysqli_stmt_affected_rows mysqli_stmt_attr_cursor_type mysqli_stmt_attr_get mysqli_stmt_attr_prefetch_rows mysqli_stmt_attr_set mysqli_stmt_attr_update_max_length mysqli_stmt_bind_param mysqli_stmt_bind_result mysqli_stmt_close mysqli_stmt_data_seek mysqli_stmt_errno mysqli_stmt_error mysqli_stmt_error_list mysqli_stmt_execute mysqli_stmt_fetch mysqli_stmt_field_count mysqli_stmt_free_result mysqli_stmt_get_result mysqli_stmt_get_warnings mysqli_stmt_init mysqli_stmt_insert_id mysqli_stmt_more_results mysqli_stmt_next_result mysqli_stmt_num_rows mysqli_stmt_param_count mysqli_stmt_prepare mysqli_stmt_reset mysqli_stmt_result_metadata mysqli_stmt_send_long_data mysqli_stmt_sqlstate mysqli_stmt_store_result mysqli_store_result mysqli_store_result_copy_data mysqli_thread_id mysqli_thread_safe mysqli_timestamp_flag mysqli_trans_cor_and_chain mysqli_trans_cor_and_no_chain mysqli_trans_cor_no_release mysqli_trans_cor_release mysqli_trans_start_read_only mysqli_trans_start_read_write mysqli_trans_start_with_consistent_snapshot mysqli_type_bit mysqli_type_blob mysqli_type_char mysqli_type_date mysqli_type_datetime mysqli_type_decimal mysqli_type_double mysqli_type_enum mysqli_type_float mysqli_type_geometry mysqli_type_int24 mysqli_type_interval mysqli_type_long mysqli_type_long_blob mysqli_type_longlong mysqli_type_medium_blob mysqli_type_newdate mysqli_type_newdecimal mysqli_type_null mysqli_type_set mysqli_type_short mysqli_type_string mysqli_type_time mysqli_type_timestamp mysqli_type_tiny mysqli_type_tiny_blob mysqli_type_var_string mysqli_type_year mysqli_unique_key_flag mysqli_unsigned_flag mysqli_use_result mysqli_warning_count mysqli_zerofill_flag n_cs_precedes n_sep_by_space n_sign_posn namespace nan natcasesort natsort ncurses_addch ncurses_addchnstr ncurses_addchstr ncurses_addnstr ncurses_addstr ncurses_all_mouse_events ncurses_assume_default_colors ncurses_attroff ncurses_attron ncurses_attrset ncurses_baudrate ncurses_beep ncurses_bkgd ncurses_bkgdset ncurses_border ncurses_bottom_panel ncurses_button1_clicked ncurses_button1_double_clicked ncurses_button1_pressed ncurses_button1_released ncurses_button1_triple_clicked ncurses_button_alt ncurses_button_ctrl ncurses_button_shift ncurses_can_change_color ncurses_cbreak ncurses_clear ncurses_clrtobot ncurses_clrtoeol ncurses_color_black ncurses_color_blue ncurses_color_content ncurses_color_cyan ncurses_color_green ncurses_color_magenta ncurses_color_red ncurses_color_set ncurses_color_white ncurses_color_yellow ncurses_curs_set ncurses_def_prog_mode ncurses_def_shell_mode ncurses_define_key ncurses_del_panel ncurses_delay_output ncurses_delch ncurses_deleteln ncurses_delwin ncurses_doupdate ncurses_echo ncurses_echochar ncurses_end ncurses_erase ncurses_erasechar ncurses_filter ncurses_flash ncurses_flushinp ncurses_getch ncurses_getmaxyx ncurses_getmouse ncurses_getyx ncurses_halfdelay ncurses_has_colors ncurses_has_ic ncurses_has_il ncurses_has_key ncurses_hide_panel ncurses_hline ncurses_inch ncurses_init ncurses_init_color ncurses_init_pair ncurses_insch ncurses_insdelln ncurses_insertln ncurses_insstr ncurses_instr ncurses_isendwin ncurses_key_a1 ncurses_key_a3 ncurses_key_b2 ncurses_key_backspace ncurses_key_beg ncurses_key_btab ncurses_key_c1 ncurses_key_c3 ncurses_key_cancel ncurses_key_catab ncurses_key_clear ncurses_key_close ncurses_key_command ncurses_key_copy ncurses_key_create ncurses_key_ctab ncurses_key_dc ncurses_key_dl ncurses_key_down ncurses_key_eic ncurses_key_end ncurses_key_eol ncurses_key_eos ncurses_key_exit ncurses_key_f0 ncurses_key_find ncurses_key_help ncurses_key_home ncurses_key_ic ncurses_key_il ncurses_key_left ncurses_key_ll ncurses_key_mark ncurses_key_max ncurses_key_message ncurses_key_mouse ncurses_key_move ncurses_key_next ncurses_key_npage ncurses_key_open ncurses_key_options ncurses_key_ppage ncurses_key_previous ncurses_key_print ncurses_key_redo ncurses_key_reference ncurses_key_refresh ncurses_key_replace ncurses_key_reset ncurses_key_restart ncurses_key_resume ncurses_key_right ncurses_key_save ncurses_key_sbeg ncurses_key_scancel ncurses_key_scommand ncurses_key_scopy ncurses_key_screate ncurses_key_sdc ncurses_key_sdl ncurses_key_select ncurses_key_send ncurses_key_seol ncurses_key_sexit ncurses_key_sf ncurses_key_sfind ncurses_key_shelp ncurses_key_shome ncurses_key_sic ncurses_key_sleft ncurses_key_smessage ncurses_key_smove ncurses_key_snext ncurses_key_soptions ncurses_key_sprevious ncurses_key_sprint ncurses_key_sr ncurses_key_sredo ncurses_key_sreplace ncurses_key_sreset ncurses_key_sright ncurses_key_srsume ncurses_key_ssave ncurses_key_ssuspend ncurses_key_stab ncurses_key_undo ncurses_key_up ncurses_keyok ncurses_keypad ncurses_killchar ncurses_longname ncurses_meta ncurses_mouse_trafo ncurses_mouseinterval ncurses_mousemask ncurses_move ncurses_move_panel ncurses_mvaddch ncurses_mvaddchnstr ncurses_mvaddchstr ncurses_mvaddnstr ncurses_mvaddstr ncurses_mvcur ncurses_mvdelch ncurses_mvgetch ncurses_mvhline ncurses_mvinch ncurses_mvvline ncurses_mvwaddstr ncurses_napms ncurses_new_panel ncurses_newpad ncurses_newwin ncurses_nl ncurses_nocbreak ncurses_noecho ncurses_nonl ncurses_noqiflush ncurses_noraw ncurses_pair_content
 ncurses_panel_above ncurses_panel_below ncurses_panel_window ncurses_pnoutrefresh ncurses_prefresh ncurses_putp ncurses_qiflush ncurses_raw ncurses_refresh ncurses_replace_panel ncurses_report_mouse_position ncurses_reset_prog_mode ncurses_reset_shell_mode ncurses_resetty ncurses_savetty ncurses_scr_dump ncurses_scr_init ncurses_scr_restore ncurses_scr_set ncurses_scrl ncurses_show_panel ncurses_slk_attr ncurses_slk_attroff ncurses_slk_attron ncurses_slk_attrset ncurses_slk_clear ncurses_slk_color ncurses_slk_init ncurses_slk_noutrefresh ncurses_slk_refresh ncurses_slk_restore ncurses_slk_set ncurses_slk_touch ncurses_standend ncurses_standout ncurses_start_color ncurses_termattrs ncurses_termname ncurses_timeout ncurses_top_panel ncurses_typeahead ncurses_ungetch ncurses_ungetmouse ncurses_update_panels ncurses_use_default_colors ncurses_use_env ncurses_use_extended_names ncurses_vidattr ncurses_vline ncurses_waddch ncurses_waddstr ncurses_wattroff ncurses_wattron ncurses_wattrset ncurses_wborder ncurses_wclear ncurses_wcolor_set ncurses_werase ncurses_wgetch ncurses_whline ncurses_wmouse_trafo ncurses_wmove ncurses_wnoutrefresh ncurses_wrefresh ncurses_wstandend ncurses_wstandout ncurses_wvline negative_sign new newt_anchor_bottom newt_anchor_left newt_anchor_right newt_anchor_top newt_arg_append newt_arg_last newt_bell newt_button newt_button_bar newt_centered_window newt_checkbox newt_checkbox_get_value newt_checkbox_set_flags newt_checkbox_set_value newt_checkbox_tree newt_checkbox_tree_add_item newt_checkbox_tree_find_item newt_checkbox_tree_get_current newt_checkbox_tree_get_entry_value newt_checkbox_tree_get_multi_selection newt_checkbox_tree_get_selection newt_checkbox_tree_multi newt_checkbox_tree_set_current newt_checkbox_tree_set_entry newt_checkbox_tree_set_entry_value newt_checkbox_tree_set_width newt_checkboxtree_collapsed newt_checkboxtree_expanded newt_checkboxtree_hide_box newt_checkboxtree_selected newt_checkboxtree_unselectable newt_checkboxtree_unselected newt_clear_key_buffer newt_cls newt_colorset_actbutton newt_colorset_actcheckbox newt_colorset_actlistbox newt_colorset_actsellistbox newt_colorset_acttextbox newt_colorset_border newt_colorset_button newt_colorset_checkbox newt_colorset_compactbutton newt_colorset_disentry newt_colorset_emptyscale newt_colorset_entry newt_colorset_fullscale newt_colorset_helpline newt_colorset_label newt_colorset_listbox newt_colorset_root newt_colorset_roottext newt_colorset_sellistbox newt_colorset_shadow newt_colorset_textbox newt_colorset_title newt_colorset_window newt_compact_button newt_component_add_callback newt_component_takes_focus newt_create_grid newt_cursor_off newt_cursor_on newt_delay newt_draw_form newt_draw_root_text newt_entry newt_entry_disabled newt_entry_get_value newt_entry_hidden newt_entry_returnexit newt_entry_scroll newt_entry_set newt_entry_set_filter newt_entry_set_flags newt_exit_component newt_exit_fdready newt_exit_hotkey newt_exit_timer newt_fd_except newt_fd_read newt_fd_write newt_finished newt_flag_border newt_flag_checkbox newt_flag_disabled newt_flag_hidden newt_flag_multiple newt_flag_nof12 newt_flag_password newt_flag_returnexit newt_flag_scroll newt_flag_selected newt_flag_showcursor newt_flag_wrap newt_flags_reset newt_flags_set newt_flags_toggle newt_form newt_form_add_component newt_form_add_components newt_form_add_hot_key newt_form_destroy newt_form_get_current newt_form_nof12 newt_form_run newt_form_set_background newt_form_set_height newt_form_set_size newt_form_set_timer newt_form_set_width newt_form_watch_fd newt_get_screen_size newt_grid_add_components_to_form newt_grid_basic_window newt_grid_component newt_grid_empty newt_grid_flag_growx newt_grid_flag_growy newt_grid_free newt_grid_get_size newt_grid_h_close_stacked newt_grid_h_stacked newt_grid_place newt_grid_set_field newt_grid_simple_window newt_grid_subgrid newt_grid_v_close_stacked newt_grid_v_stacked newt_grid_wrapped_window newt_grid_wrapped_window_at newt_init newt_key_bkspc newt_key_delete newt_key_down newt_key_end newt_key_enter newt_key_escape newt_key_extra_base newt_key_f1 newt_key_f10 newt_key_f11 newt_key_f12 newt_key_f2 newt_key_f3 newt_key_f4 newt_key_f5 newt_key_f6 newt_key_f7 newt_key_f8 newt_key_f9 newt_key_home newt_key_insert newt_key_left newt_key_pgdn newt_key_pgup newt_key_resize newt_key_return newt_key_right newt_key_suspend newt_key_tab newt_key_untab newt_key_up newt_label newt_label_set_text newt_listbox newt_listbox_append_entry newt_listbox_clear newt_listbox_clear_selection newt_listbox_delete_entry newt_listbox_get_current newt_listbox_get_selection newt_listbox_insert_entry newt_listbox_item_count newt_listbox_returnexit newt_listbox_select_item newt_listbox_set_current newt_listbox_set_current_by_key newt_listbox_set_data newt_listbox_set_entry newt_listbox_set_width newt_listitem newt_listitem_get_data newt_listitem_set newt_open_window newt_pop_help_line newt_pop_window newt_push_help_line newt_radio_get_current newt_radiobutton newt_redraw_help_line newt_reflow_text newt_refresh newt_resize_screen newt_resume newt_run_form newt_scale newt_scale_set newt_scrollbar_set newt_set_help_callback newt_set_suspend_callback newt_suspend newt_textbox newt_textbox_get_num_lines newt_textbox_reflowed newt_textbox_scroll newt_textbox_set_height newt_textbox_set_text newt_textbox_wrap newt_vertical_scrollbar newt_wait_for_key newt_win_choice newt_win_entries newt_win_menu newt_win_message newt_win_messagev newt_win_ternary next ngettext nil nl2br nl_langinfo noexpr norm_ignorecase norm_ignorekanatype norm_ignorekashida norm_ignorenonspace norm_ignoresymbols norm_ignorewidth normalizer_is_normalized normalizer_normalize nostr nthmac null number_format numfmt_create numfmt_format numfmt_format_currency numfmt_get_attribute numfmt_get_error_code numfmt_get_error_message numfmt_get_locale numfmt_get_pattern numfmt_get_symbol numfmt_get_text_attribute numfmt_parse numfmt_parse_currency numfmt_set_attribute numfmt_set_pattern numfmt_set_symbol numfmt_set_text_attribute o_append o_async o_creat o_excl o_ndelay o_noctty o_nonblock o_rdonly o_rdwr o_sync o_trunc o_wronly ob_clean ob_deflatehandler ob_end_clean ob_end_flush ob_etaghandler ob_flush ob_get_clean ob_get_contents ob_get_flush ob_get_length ob_get_level ob_get_status ob_gzhandler ob_iconv_handler ob_implicit_flush ob_inflatehandler ob_list_handlers ob_start ob_tidyhandler object oci_assoc oci_b_bfile oci_b_bin oci_b_blob oci_b_bol oci_b_cfilee oci_b_clob oci_b_cursor oci_b_int oci_b_nty oci_b_num oci_b_rowid oci_bind_array_by_name oci_bind_by_name oci_both oci_cancel oci_client_version oci_close oci_commit oci_commit_on_success oci_connect oci_cred_ext oci_d_file oci_d_lob oci_d_rowid oci_default oci_define_by_name oci_describe_only oci_dtype_file oci_dtype_lob oci_dtype_rowid oci_error oci_exact_fetch oci_execute oci_fetch oci_fetch_all oci_fetch_array oci_fetch_assoc oci_fetch_object oci_fetch_row oci_fetchstatement_by_column oci_fetchstatement_by_row oci_field_is_null oci_field_name oci_field_precision oci_field_scale oci_field_size oci_field_type oci_field_type_raw oci_free_descriptor oci_free_statement oci_get_implicit_resultset oci_internal_debug oci_lob_buffer_free oci_lob_copy oci_lob_is_equal oci_new_collection oci_new_connect oci_new_cursor oci_new_descriptor oci_no_auto_commit oci_num oci_num_fields oci_num_rows oci_parse oci_password_change oci_pconnect oci_result oci_return_lobs oci_return_nulls oci_rollback oci_seek_cur oci_seek_end oci_seek_set oci_server_version oci_set_action oci_set_client_identifier oci_set_client_info oci_set_edition oci_set_module_name oci_set_prefetch oci_statement_type oci_sysdate oci_sysdba oci_sysoper oci_temp_blob oci_temp_clob ocibindbyname ocicolumnisnull ocicolumnname ocicolumnsize ocicolumntype ocicommit ocidefinebyname ocierror ociexecute ocifetch ocifetchinto ocifetchstatement ocifreestatement ocilogoff ocilogon ocinewcursor ocinewdescriptor ocinlogon ocinumcols ociparse ociplogon ociresult ocirollback ocirowcount ociserverversion ocistatementtype octdec odbc_autocommit odbc_binmode odbc_binmode_convert odbc_binmode_passthru odbc_binmode_return odbc_close odbc_close_all odbc_columnprivileges odbc_columns odbc_commit odbc_connect odbc_cursor odbc_data_source odbc_do odbc_error odbc_errormsg odbc_exec odbc_execute odbc_fetch_array odbc_fetch_into odbc_fetch_object odbc_fetch_row odbc_field_len odbc_field_name odbc_field_num odbc_field_precision odbc_field_scale odbc_field_type odbc_foreignkeys odbc_free_result odbc_gettypeinfo odbc_longreadlen odbc_next_result odbc_num_fields odbc_num_rows odbc_pconnect odbc_prepare odbc_primarykeys odbc_procedurecolumns odbc_procedures odbc_result odbc_result_all odbc_rollback odbc_setoption odbc_specialcolumns odbc_statistics odbc_tableprivileges odbc_tables odbc_type oggvorbis_pcm_s16_be oggvorbis_pcm_s16_le oggvorbis_pcm_s8 oggvorbis_pcm_u16_be oggvorbis_pcm_u16_le oggvorbis_pcm_u8 old_function op_anonymous op_debug op_expunge op_halfopen op_prototype op_readonly op_secure op_shortcache op_silent opcache_compile_file opcache_get_configuration opcache_get_status opcache_invalidate opcache_is_script_cached opcache_reset openal_buffer_create openal_buffer_data openal_buffer_destroy openal_buffer_get openal_buffer_loadwav openal_context_create openal_context_current openal_context_destroy openal_context_process openal_context_suspend openal_device_close openal_device_open openal_listener_get openal_listener_set openal_source_create openal_source_destroy openal_source_get openal_source_pause openal_source_play openal_source_rewind openal_source_set openal_source_stop openal_stream opendir openlog openssl_algo_dss1 openssl_algo_md4 openssl_algo_md5 openssl_algo_rmd160 openssl_algo_sha1
 openssl_algo_sha224 openssl_algo_sha256 openssl_algo_sha384 openssl_algo_sha512 openssl_cipher_3des openssl_cipher_aes_128_cbc openssl_cipher_aes_192_cbc openssl_cipher_aes_256_cbc openssl_cipher_des openssl_cipher_iv_length openssl_cipher_rc2_128 openssl_cipher_rc2_40 openssl_cipher_rc2_64 openssl_csr_export openssl_csr_export_to_file openssl_csr_get_public_key openssl_csr_get_subject openssl_csr_new openssl_csr_sign openssl_decrypt openssl_default_stream_ciphers openssl_dh_compute_key openssl_digest openssl_encrypt openssl_error_string openssl_free_key openssl_get_cert_locations openssl_get_cipher_methods openssl_get_md_methods openssl_get_privatekey openssl_get_publickey openssl_keytype_dh openssl_keytype_dsa openssl_keytype_ec openssl_keytype_rsa openssl_no_padding openssl_open openssl_pbkdf2 openssl_pkcs12_export openssl_pkcs12_export_to_file openssl_pkcs12_read openssl_pkcs1_oaep_padding openssl_pkcs1_padding openssl_pkcs7_decrypt openssl_pkcs7_encrypt openssl_pkcs7_sign openssl_pkcs7_verify openssl_pkey_export openssl_pkey_export_to_file openssl_pkey_free openssl_pkey_get_details openssl_pkey_get_private openssl_pkey_get_public openssl_pkey_new openssl_private_decrypt openssl_private_encrypt openssl_public_decrypt openssl_public_encrypt openssl_random_pseudo_bytes openssl_raw_data openssl_seal openssl_sign openssl_spki_export openssl_spki_export_challenge openssl_spki_new openssl_spki_verify openssl_sslv23_padding openssl_tlsext_server_name openssl_verify openssl_version_number openssl_version_text openssl_x509_check_private_key openssl_x509_checkpurpose openssl_x509_export openssl_x509_export_to_file openssl_x509_fingerprint openssl_x509_free openssl_x509_parse openssl_x509_read openssl_zero_padding or ord output_add_rewrite_var output_reset_rewrite_vars override_function p_cs_precedes p_sep_by_space p_sign_posn pack parent parse_ini_file parse_ini_string parse_str parse_url parsekit_compile_file parsekit_compile_string parsekit_extended_value parsekit_func_arginfo parsekit_is_const parsekit_is_tmp_var parsekit_is_unused parsekit_is_var parsekit_quiet parsekit_result_const parsekit_result_ea_type parsekit_result_jmp_addr parsekit_result_oparray parsekit_result_opline parsekit_result_var parsekit_simple parsekit_usage_unknown parsekit_zend_add parsekit_zend_add_array_element parsekit_zend_add_char parsekit_zend_add_interface parsekit_zend_add_string parsekit_zend_add_var parsekit_zend_assign parsekit_zend_assign_add parsekit_zend_assign_bw_and parsekit_zend_assign_bw_or parsekit_zend_assign_bw_xor parsekit_zend_assign_concat parsekit_zend_assign_dim parsekit_zend_assign_div parsekit_zend_assign_mod parsekit_zend_assign_mul parsekit_zend_assign_obj parsekit_zend_assign_ref parsekit_zend_assign_sl parsekit_zend_assign_sr parsekit_zend_assign_sub parsekit_zend_begin_silence parsekit_zend_bool parsekit_zend_bool_not parsekit_zend_bool_xor parsekit_zend_brk parsekit_zend_bw_and parsekit_zend_bw_not parsekit_zend_bw_or parsekit_zend_bw_xor parsekit_zend_case parsekit_zend_cast parsekit_zend_catch parsekit_zend_clone parsekit_zend_concat parsekit_zend_cont parsekit_zend_declare_class parsekit_zend_declare_function parsekit_zend_declare_inherited_class parsekit_zend_div parsekit_zend_do_fcall parsekit_zend_do_fcall_by_name parsekit_zend_echo parsekit_zend_end_silence parsekit_zend_eval_code parsekit_zend_exit parsekit_zend_ext_fcall_begin parsekit_zend_ext_fcall_end parsekit_zend_ext_nop parsekit_zend_ext_stmt parsekit_zend_fe_fetch parsekit_zend_fe_reset parsekit_zend_fetch_class parsekit_zend_fetch_constant parsekit_zend_fetch_dim_func_arg parsekit_zend_fetch_dim_is parsekit_zend_fetch_dim_r parsekit_zend_fetch_dim_rw parsekit_zend_fetch_dim_tmp_var parsekit_zend_fetch_dim_unset parsekit_zend_fetch_dim_w parsekit_zend_fetch_func_arg parsekit_zend_fetch_is parsekit_zend_fetch_obj_func_arg parsekit_zend_fetch_obj_is parsekit_zend_fetch_obj_r parsekit_zend_fetch_obj_rw parsekit_zend_fetch_obj_unset parsekit_zend_fetch_obj_w parsekit_zend_fetch_r parsekit_zend_fetch_rw parsekit_zend_fetch_unset parsekit_zend_fetch_w parsekit_zend_free parsekit_zend_handle_exception parsekit_zend_import_class parsekit_zend_import_const parsekit_zend_import_function parsekit_zend_include_or_eval parsekit_zend_init_array parsekit_zend_init_ctor_call parsekit_zend_init_fcall_by_name parsekit_zend_init_method_call parsekit_zend_init_static_method_call parsekit_zend_init_string parsekit_zend_instanceof parsekit_zend_internal_class parsekit_zend_internal_function parsekit_zend_is_equal parsekit_zend_is_identical parsekit_zend_is_not_equal parsekit_zend_is_not_identical parsekit_zend_is_smaller parsekit_zend_is_smaller_or_equal parsekit_zend_isset_isempty parsekit_zend_isset_isempty_dim_obj parsekit_zend_isset_isempty_prop_obj parsekit_zend_isset_isempty_var parsekit_zend_jmp parsekit_zend_jmp_no_ctor parsekit_zend_jmpnz parsekit_zend_jmpnz_ex parsekit_zend_jmpz parsekit_zend_jmpz_ex parsekit_zend_jmpznz parsekit_zend_mod parsekit_zend_mul parsekit_zend_new parsekit_zend_nop parsekit_zend_op_data parsekit_zend_overloaded_function parsekit_zend_overloaded_function_temporary parsekit_zend_post_dec parsekit_zend_post_dec_obj parsekit_zend_post_inc parsekit_zend_post_inc_obj parsekit_zend_pre_dec parsekit_zend_pre_dec_obj parsekit_zend_pre_inc parsekit_zend_pre_inc_obj parsekit_zend_print parsekit_zend_qm_assign parsekit_zend_raise_abstract_error parsekit_zend_recv parsekit_zend_recv_init parsekit_zend_return parsekit_zend_send_ref parsekit_zend_send_val parsekit_zend_send_var parsekit_zend_send_var_no_ref parsekit_zend_sl parsekit_zend_sr parsekit_zend_sub parsekit_zend_switch_free parsekit_zend_throw parsekit_zend_ticks parsekit_zend_unset_dim_obj parsekit_zend_unset_var parsekit_zend_user_class parsekit_zend_user_function parsekit_zend_verify_abstract_class passthru password_bcrypt password_bcrypt_default_cost password_default password_get_info password_hash password_needs_rehash password_verify path_separator pathinfo pathinfo_basename pathinfo_dirname pathinfo_extension pathinfo_filename pclose pcntl_alarm pcntl_errno pcntl_exec pcntl_fork pcntl_get_last_error pcntl_getpriority pcntl_setpriority pcntl_signal pcntl_signal_dispatch pcntl_sigprocmask pcntl_sigtimedwait pcntl_sigwaitinfo pcntl_strerror pcntl_wait pcntl_waitpid pcntl_wexitstatus pcntl_wifexited pcntl_wifsignaled pcntl_wifstopped pcntl_wstopsig pcntl_wtermsig pcre_version pdf_activate_item pdf_add_annotation pdf_add_bookmark pdf_add_launchlink pdf_add_locallink pdf_add_nameddest pdf_add_note pdf_add_outline pdf_add_pdflink pdf_add_table_cell pdf_add_textflow pdf_add_thumbnail pdf_add_weblink pdf_arc pdf_arcn pdf_attach_file pdf_begin_document pdf_begin_font pdf_begin_glyph pdf_begin_item pdf_begin_layer pdf_begin_page pdf_begin_page_ext pdf_begin_pattern pdf_begin_template pdf_begin_template_ext pdf_circle pdf_clip pdf_close pdf_close_image pdf_close_pdi pdf_close_pdi_page pdf_closepath pdf_closepath_fill_stroke pdf_closepath_stroke pdf_concat pdf_continue_text pdf_create_3dview pdf_create_action pdf_create_annotation pdf_create_bookmark pdf_create_field pdf_create_fieldgroup pdf_create_gstate pdf_create_pvf pdf_create_textflow pdf_curveto pdf_define_layer pdf_delete pdf_delete_pvf pdf_delete_table pdf_delete_textflow pdf_encoding_set_char pdf_end_document pdf_end_font pdf_end_glyph pdf_end_item pdf_end_layer pdf_end_page pdf_end_page_ext pdf_end_pattern pdf_end_template pdf_endpath pdf_fill pdf_fill_imageblock pdf_fill_pdfblock pdf_fill_stroke pdf_fill_textblock pdf_findfont pdf_fit_image pdf_fit_pdi_page pdf_fit_table pdf_fit_textflow pdf_fit_textline pdf_get_apiname pdf_get_buffer pdf_get_errmsg pdf_get_errnum pdf_get_font pdf_get_fontname pdf_get_fontsize pdf_get_image_height pdf_get_image_width pdf_get_majorversion pdf_get_minorversion pdf_get_parameter pdf_get_pdi_parameter pdf_get_pdi_value pdf_get_value pdf_info_font pdf_info_matchbox pdf_info_table pdf_info_textflow pdf_info_textline pdf_initgraphics pdf_lineto pdf_load_3ddata pdf_load_font pdf_load_iccprofile pdf_load_image pdf_makespotcolor pdf_moveto pdf_new pdf_open_ccitt pdf_open_file pdf_open_gif pdf_open_image pdf_open_image_file pdf_open_jpeg pdf_open_memory_image pdf_open_pdi pdf_open_pdi_document pdf_open_pdi_page pdf_open_tiff pdf_pcos_get_number pdf_pcos_get_stream pdf_pcos_get_string pdf_place_image pdf_place_pdi_page pdf_process_pdi pdf_rect pdf_restore pdf_resume_page pdf_rotate pdf_save pdf_scale pdf_set_border_color pdf_set_border_dash pdf_set_border_style pdf_set_char_spacing pdf_set_duration pdf_set_gstate pdf_set_horiz_scaling pdf_set_info pdf_set_info_author pdf_set_info_creator pdf_set_info_keywords pdf_set_info_subject pdf_set_info_title pdf_set_layer_dependency pdf_set_leading pdf_set_parameter pdf_set_text_matrix pdf_set_text_pos pdf_set_text_rendering pdf_set_text_rise pdf_set_value pdf_set_word_spacing pdf_setcolor pdf_setdash pdf_setdashpattern pdf_setflat pdf_setfont pdf_setgray pdf_setgray_fill pdf_setgray_stroke pdf_setlinecap pdf_setlinejoin pdf_setlinewidth pdf_setmatrix pdf_setmiterlimit pdf_setpolydash pdf_setrgbcolor pdf_setrgbcolor_fill pdf_setrgbcolor_stroke pdf_shading pdf_shading_pattern pdf_shfill pdf_show pdf_show_boxed pdf_show_xy pdf_skew pdf_stringwidth pdf_stroke pdf_suspend_page pdf_translate pdf_utf16_to_utf8 pdf_utf32_to_utf16 pdf_utf8_to_utf16 pdo_drivers pear_extension_dir pear_install_dir pfsockopen pg_affected_rows pg_cancel_query pg_client_encoding pg_clientencoding pg_close pg_cmdtuples pg_connect pg_connect_poll pg_connection_busy pg_connection_reset pg_connection_status pg_consume_input pg_convert pg_copy_from pg_copy_to pg_dbname pg_delete pg_end_copy pg_errormessage pg_escape_bytea pg_escape_identifier pg_escape_literal pg_escape_string pg_exec
 pg_execute pg_fetch_all pg_fetch_all_columns pg_fetch_array pg_fetch_assoc pg_fetch_object pg_fetch_result pg_fetch_row pg_field_is_null pg_field_name pg_field_num pg_field_prtlen pg_field_size pg_field_table pg_field_type pg_field_type_oid pg_fieldisnull pg_fieldname pg_fieldnum pg_fieldprtlen pg_fieldsize pg_fieldtype pg_flush pg_free_result pg_freeresult pg_get_notify pg_get_pid pg_get_result pg_getlastoid pg_host pg_insert pg_last_error pg_last_notice pg_last_oid pg_lo_close pg_lo_create pg_lo_export pg_lo_import pg_lo_open pg_lo_read pg_lo_read_all pg_lo_seek pg_lo_tell pg_lo_truncate pg_lo_unlink pg_lo_write pg_loclose pg_locreate pg_loexport pg_loimport pg_loopen pg_loread pg_loreadall pg_lounlink pg_lowrite pg_meta_data pg_num_fields pg_num_rows pg_numfields pg_numrows pg_options pg_parameter_status pg_pconnect pg_ping pg_port pg_prepare pg_put_line pg_query pg_query_params pg_result pg_result_error pg_result_error_field pg_result_seek pg_result_status pg_select pg_send_execute pg_send_prepare pg_send_query pg_send_query_params pg_set_client_encoding pg_set_error_verbosity pg_setclientencoding pg_socket pg_trace pg_transaction_status pg_tty pg_unescape_bytea pg_untrace pg_update pg_version pgsql_assoc pgsql_bad_response pgsql_both pgsql_command_ok pgsql_connect_async pgsql_connect_force_new pgsql_connection_auth_ok pgsql_connection_awaiting_response pgsql_connection_bad pgsql_connection_made pgsql_connection_ok pgsql_connection_setenv pgsql_connection_started pgsql_conv_force_null pgsql_conv_ignore_default pgsql_conv_ignore_not_null pgsql_copy_in pgsql_copy_out pgsql_diag_context pgsql_diag_internal_position pgsql_diag_internal_query pgsql_diag_message_detail pgsql_diag_message_hint pgsql_diag_message_primary pgsql_diag_severity pgsql_diag_source_file pgsql_diag_source_function pgsql_diag_source_line pgsql_diag_sqlstate pgsql_diag_statement_position pgsql_dml_async pgsql_dml_escape pgsql_dml_exec pgsql_dml_no_conv pgsql_dml_string pgsql_empty_query pgsql_errors_default pgsql_errors_terse pgsql_errors_verbose pgsql_fatal_error pgsql_libpq_version pgsql_libpq_version_str pgsql_nonfatal_error pgsql_num pgsql_polling_active pgsql_polling_failed pgsql_polling_ok pgsql_polling_reading pgsql_polling_writing pgsql_seek_cur pgsql_seek_end pgsql_seek_set pgsql_status_long pgsql_status_string pgsql_transaction_active pgsql_transaction_idle pgsql_transaction_inerror pgsql_transaction_intrans pgsql_transaction_unknown pgsql_tuples_ok php_binary php_binary_read php_bindir php_check_syntax php_config_file_path php_config_file_scan_dir php_datadir php_debug php_egg_logo_guid php_eol php_extension_dir php_extra_version php_ini_loaded_file php_ini_scanned_files php_int_max php_int_size php_libdir php_localstatedir php_logo_guid php_major_version php_mandir php_maxpathlen php_minor_version php_normal_read php_os php_output_handler_clean php_output_handler_cleanable php_output_handler_cont php_output_handler_disabled php_output_handler_end php_output_handler_final php_output_handler_flush php_output_handler_flushable php_output_handler_removable php_output_handler_start php_output_handler_started php_output_handler_stdflags php_output_handler_write php_prefix php_query_rfc1738 php_query_rfc3986 php_real_logo_guid php_release_version php_round_half_down php_round_half_even php_round_half_odd php_round_half_up php_sapi php_sapi_name php_session_active php_session_disabled php_session_none php_shlib_suffix php_strip_whitespace php_svn_auth_param_ignore_ssl_verify_errors php_sysconfdir php_uname php_url_fragment php_url_host php_url_pass php_url_path php_url_port php_url_query php_url_scheme php_url_user php_version php_version_id php_windows_nt_domain_controller php_windows_nt_server php_windows_nt_workstation php_windows_version_build php_windows_version_major php_windows_version_minor php_windows_version_platform php_windows_version_producttype php_windows_version_sp_major php_windows_version_sp_minor php_windows_version_suitemask php_zts phpcredits phpinfo phpversion pi pkcs7_binary pkcs7_detached pkcs7_noattr pkcs7_nocerts pkcs7_nochain pkcs7_nointern pkcs7_nosigs pkcs7_noverify pkcs7_text pm_str png2wbmp png_all_filters png_filter_avg png_filter_none png_filter_paeth png_filter_sub png_filter_up png_no_filter poll_err poll_hup poll_in poll_msg poll_out poll_pri popen pos positive_sign posix_access posix_ctermid posix_errno posix_f_ok posix_get_last_error posix_getcwd posix_getegid posix_geteuid posix_getgid posix_getgrgid posix_getgrnam posix_getgroups posix_getlogin posix_getpgid posix_getpgrp posix_getpid posix_getppid posix_getpwnam posix_getpwuid posix_getrlimit posix_getsid posix_getuid posix_initgroups posix_isatty posix_kill posix_mkfifo posix_mknod posix_r_ok posix_s_ifblk posix_s_ifchr posix_s_ififo posix_s_ifreg posix_s_ifsock posix_setegid posix_seteuid posix_setgid posix_setpgid posix_setrlimit posix_setsid posix_setuid posix_strerror posix_times posix_ttyname posix_uname posix_w_ok posix_x_ok pow preg_backtrack_limit_error preg_bad_utf8_error preg_bad_utf8_offset_error preg_filter preg_grep preg_grep_invert preg_internal_error preg_last_error preg_match preg_match_all preg_no_error preg_offset_capture preg_pattern_order preg_quote preg_recursion_limit_error preg_replace preg_replace_callback preg_replace_callback_array preg_set_order preg_split preg_split_delim_capture preg_split_no_empty preg_split_offset_capture prev print print_r printf private proc_close proc_get_status proc_nice proc_open proc_terminate prof_trace property_exists protected ps_add_bookmark ps_add_launchlink ps_add_locallink ps_add_note ps_add_pdflink ps_add_weblink ps_arc ps_arcn ps_begin_page ps_begin_pattern ps_begin_template ps_circle ps_clip ps_close ps_close_image ps_closepath ps_closepath_stroke ps_continue_text ps_curveto ps_delete ps_end_page ps_end_pattern ps_end_template ps_fill ps_fill_stroke ps_findfont ps_get_buffer ps_get_parameter ps_get_value ps_hyphenate ps_include_file ps_linecap_butt ps_linecap_round ps_linecap_squared ps_linejoin_bevel ps_linejoin_miter ps_linejoin_round ps_lineto ps_makespotcolor ps_moveto ps_new ps_open_file ps_open_image ps_open_image_file ps_open_memory_image ps_place_image ps_rect ps_restore ps_rotate ps_save ps_scale ps_set_border_color ps_set_border_dash ps_set_border_style ps_set_info ps_set_parameter ps_set_text_pos ps_set_value ps_setcolor ps_setdash ps_setflat ps_setfont ps_setgray ps_setlinecap ps_setlinejoin ps_setlinewidth ps_setmiterlimit ps_setoverprintmode ps_setpolydash ps_shading ps_shading_pattern ps_shfill ps_show ps_show2 ps_show_boxed ps_show_xy ps_show_xy2 ps_string_geometry ps_stringwidth ps_stroke ps_symbol ps_symbol_name ps_symbol_width ps_translate psfs_err_fatal psfs_feed_me psfs_flag_flush_close psfs_flag_flush_inc psfs_flag_normal psfs_pass_on pspell_add_to_personal pspell_add_to_session pspell_bad_spellers pspell_check pspell_clear_session pspell_config_create pspell_config_data_dir pspell_config_dict_dir pspell_config_ignore pspell_config_mode pspell_config_personal pspell_config_repl pspell_config_runtogether pspell_config_save_repl pspell_fast pspell_new pspell_new_config pspell_new_personal pspell_normal pspell_run_together pspell_save_wordlist pspell_store_replacement pspell_suggest pthreads_allow_headers pthreads_inherit_all pthreads_inherit_classes pthreads_inherit_comments pthreads_inherit_constants pthreads_inherit_functions pthreads_inherit_includes pthreads_inherit_ini pthreads_inherit_none public putenv px_close px_create_fp px_date2string px_delete px_delete_record px_field_alpha px_field_autoinc px_field_bcd px_field_blob px_field_bytes px_field_currency px_field_date px_field_fmtmemoblob px_field_graphic px_field_logical px_field_long px_field_memoblob px_field_number px_field_ole px_field_short px_field_time px_field_timestamp px_file_inc_sec_index px_file_inc_sec_index_g px_file_index_db px_file_non_inc_sec_index px_file_non_inc_sec_index_g px_file_non_index_db px_file_prim_index px_file_sec_index px_file_sec_index_g px_get_field px_get_info px_get_parameter px_get_record px_get_schema px_get_value px_insert_record px_keytolower px_keytoupper px_new px_numfields px_numrecords px_open_fp px_put_record px_retrieve_record px_set_blob_file px_set_parameter px_set_tablename px_set_targetencoding px_set_value px_timestamp2string px_update_record quoted_printable_decode quoted_printable_encode quotemeta rad2deg radius_access_accept radius_access_challenge radius_access_reject radius_access_request radius_accounting_off radius_accounting_on radius_accounting_request radius_accounting_response radius_acct_authentic radius_acct_delay_time radius_acct_input_octets radius_acct_input_packets radius_acct_link_count radius_acct_multi_session_id radius_acct_open radius_acct_output_octets radius_acct_output_packets radius_acct_session_id radius_acct_session_time radius_acct_status_type radius_acct_terminate_cause radius_add_server radius_administrative radius_adsl_cap radius_adsl_dmt radius_arap radius_async radius_auth_local radius_auth_open radius_auth_radius radius_auth_remote radius_authenticate_only radius_cable radius_callback_framed radius_callback_id radius_callback_login radius_callback_nas_prompt radius_callback_number radius_called_station_id radius_calling_station_id radius_chap_challenge radius_chap_password radius_class radius_close radius_coa_ack radius_coa_nak radius_coa_request radius_comp_ipxhdr radius_comp_none radius_comp_stac_lzs radius_comp_vj radius_config radius_connect_info radius_create_request radius_cvt_addr radius_cvt_int radius_cvt_string radius_demangle radius_demangle_mppe_key radius_disconnect_ack radius_disconnect_nak radius_disconnect_request radius_ethernet radius_filter_id radius_framed radius_framed_appletalk_link radius_framed_appletalk_network radius_framed_appletalk_zone
 radius_framed_compression radius_framed_ip_address radius_framed_ip_netmask radius_framed_ipx_network radius_framed_mtu radius_framed_protocol radius_framed_route radius_framed_routing radius_g_3_fax radius_gandalf radius_get_attr radius_get_tagged_attr_data radius_get_tagged_attr_tag radius_get_vendor_attr radius_hdlc_clear_channel radius_idle_timeout radius_idsl radius_isdn_async_v110 radius_isdn_async_v120 radius_isdn_sync radius_login radius_login_ip_host radius_login_lat_group radius_login_lat_node radius_login_lat_port radius_login_lat_service radius_login_service radius_login_tcp_port radius_microsoft_ms_acct_auth_type radius_microsoft_ms_acct_eap_type radius_microsoft_ms_arap_challenge radius_microsoft_ms_arap_password_change_reason radius_microsoft_ms_bap_usage radius_microsoft_ms_chap2_pw radius_microsoft_ms_chap2_response radius_microsoft_ms_chap2_success radius_microsoft_ms_chap_challenge radius_microsoft_ms_chap_domain radius_microsoft_ms_chap_error radius_microsoft_ms_chap_lm_enc_pw radius_microsoft_ms_chap_mppe_keys radius_microsoft_ms_chap_nt_enc_pw radius_microsoft_ms_chap_pw_1 radius_microsoft_ms_chap_pw_2 radius_microsoft_ms_chap_response radius_microsoft_ms_filter radius_microsoft_ms_link_drop_time_limit radius_microsoft_ms_link_utilization_threshold radius_microsoft_ms_mppe_encryption_policy radius_microsoft_ms_mppe_encryption_types radius_microsoft_ms_mppe_recv_key radius_microsoft_ms_mppe_send_key radius_microsoft_ms_new_arap_password radius_microsoft_ms_old_arap_password radius_microsoft_ms_primary_dns_server radius_microsoft_ms_primary_nbns_server radius_microsoft_ms_ras_vendor radius_microsoft_ms_ras_version radius_microsoft_ms_secondary_dns_server radius_microsoft_ms_secondary_nbns_server radius_mppe_key_len radius_nas_identifier radius_nas_ip_address radius_nas_port radius_nas_port_type radius_nas_prompt radius_option_salt radius_option_tagged radius_outbound radius_piafs radius_port_limit radius_ppp radius_proxy_state radius_put_addr radius_put_attr radius_put_int radius_put_string radius_put_vendor_addr radius_put_vendor_attr radius_put_vendor_int radius_put_vendor_string radius_reply_message radius_request_authenticator radius_salt_encrypt_attr radius_sdsl radius_send_request radius_server_secret radius_service_type radius_session_timeout radius_slip radius_start radius_state radius_stop radius_strerror radius_sync radius_term_admin_reboot radius_term_admin_reset radius_term_callback radius_term_host_request radius_term_idle_timeout radius_term_lost_carrier radius_term_lost_service radius_term_nas_error radius_term_nas_reboot radius_term_nas_request radius_term_port_error radius_term_port_preempted radius_term_port_suspended radius_term_port_unneeded radius_term_service_unavailable radius_term_session_timeout radius_term_user_error radius_term_user_request radius_termination_action radius_user_name radius_user_password radius_vendor_microsoft radius_vendor_specific radius_virtual radius_wireless_ieee_802_11 radius_wireless_other radius_x_25 radius_x_75 radius_xdsl radius_xylogics radixchar rand random_bytes random_int range rar_host_beos rar_host_msdos rar_host_os2 rar_host_unix rar_host_win32 rar_wrapper_cache_stats rawurldecode rawurlencode read_exif_data readdir readfile readgzfile readline readline_add_history readline_callback_handler_install readline_callback_handler_remove readline_callback_read_char readline_clear_history readline_completion_function readline_info readline_list_history readline_on_new_line readline_read_history readline_redisplay readline_write_history readlink real realpath realpath_cache_get realpath_cache_size register_shutdown_function register_tick_function rename rename_function require require_once reset resource resourcebundle_count resourcebundle_create resourcebundle_get resourcebundle_get_error_code resourcebundle_get_error_message resourcebundle_locales restore_error_handler restore_exception_handler restore_include_path return rewind rewinddir rmdir round rpm_close rpm_get_tag rpm_is_valid rpm_open rpm_version rpmreader_arch rpmreader_archivesize rpmreader_basenames rpmreader_buildarchs rpmreader_buildhost rpmreader_buildtime rpmreader_cachectime rpmreader_cachepkgmtime rpmreader_cachepkgpath rpmreader_cachepkgsize rpmreader_changelogname rpmreader_changelogtext rpmreader_changelogtime rpmreader_classdict rpmreader_conflictflags rpmreader_conflictname rpmreader_conflictversion rpmreader_cookie rpmreader_copyright rpmreader_dependsdict rpmreader_description rpmreader_dirindexes rpmreader_dirnames rpmreader_distribution rpmreader_disturl rpmreader_epoch rpmreader_excludearch rpmreader_excludeos rpmreader_exclusivearch rpmreader_exclusiveos rpmreader_fileclass rpmreader_filecolors rpmreader_filecontexts rpmreader_filedependsn rpmreader_filedependsx rpmreader_filedevices rpmreader_fileflags rpmreader_filegroupname rpmreader_fileinodes rpmreader_filelangs rpmreader_filelinktos rpmreader_filemd5s rpmreader_filemodes rpmreader_filemtimes rpmreader_filerdevs rpmreader_filesizes rpmreader_filestates rpmreader_fileusername rpmreader_fileverifyflags rpmreader_fscontexts rpmreader_gif rpmreader_group rpmreader_icon rpmreader_installcolor rpmreader_installtid rpmreader_installtime rpmreader_instprefixes rpmreader_license rpmreader_maximum rpmreader_minimum rpmreader_name rpmreader_obsoleteflags rpmreader_obsoletename rpmreader_obsoletes rpmreader_obsoleteversion rpmreader_oldfilenames rpmreader_optflags rpmreader_os rpmreader_packager rpmreader_patch rpmreader_patchesflags rpmreader_patchesname rpmreader_patchesversion rpmreader_payloadcompressor rpmreader_payloadflags rpmreader_payloadformat rpmreader_platform rpmreader_policies rpmreader_postin rpmreader_postinprog rpmreader_postun rpmreader_postunprog rpmreader_prefixes rpmreader_prein rpmreader_preinprog rpmreader_preun rpmreader_preunprog rpmreader_provideflags rpmreader_providename rpmreader_provides rpmreader_provideversion rpmreader_recontexts rpmreader_release rpmreader_removetid rpmreader_requireflags rpmreader_requirename rpmreader_requireversion rpmreader_rhnplatform rpmreader_rpmversion rpmreader_serial rpmreader_size rpmreader_source rpmreader_sourcepkgid rpmreader_sourcerpm rpmreader_summary rpmreader_triggerflags rpmreader_triggerindex rpmreader_triggername rpmreader_triggerscriptprog rpmreader_triggerscripts rpmreader_triggerversion rpmreader_url rpmreader_vendor rpmreader_verifyscript rpmreader_verifyscriptprog rpmreader_version rpmreader_xpm rsort rtrim s_all s_executor s_files s_include s_internal s_irgrp s_iroth s_irusr s_irwxg s_irwxo s_irwxu s_iwgrp s_iwoth s_iwusr s_ixgrp s_ixoth s_ixusr s_mail s_memory s_misc s_session s_sql s_vars sa_all sa_messages sa_recent sa_uidnext sa_uidvalidity sa_unseen scandir scandir_sort_ascending scandir_sort_descending scandir_sort_none se_free se_noprefetch se_uid seek_cur seek_end seek_set segv_accerr segv_maperr sem_acquire sem_get sem_release sem_remove serialize session_abort session_cache_expire session_cache_limiter session_commit session_decode session_destroy session_encode session_get_cookie_params session_id session_is_registered session_module_name session_name session_pgsql_add_error session_pgsql_get_error session_pgsql_get_field session_pgsql_reset session_pgsql_set_field session_pgsql_status session_regenerate_id session_register session_register_shutdown session_reset session_save_path session_set_cookie_params session_set_save_handler session_start session_status session_unregister session_unset session_write_close set_error_handler set_exception_handler set_file_buffer set_include_path set_magic_quotes_runtime set_socket_blocking set_time_limit setcookie setlocale setproctitle setrawcookie setthreadtitle settype sha1 sha1_file shell_exec shm_attach shm_detach shm_get_var shm_has_var shm_put_var shm_remove shm_remove_var shmop_close shmop_delete shmop_open shmop_read shmop_size shmop_write show_source shuffle si_asyncio si_kernel si_msggq si_noinfo si_queue si_sigio si_timer si_tkill si_user sid sig_block sig_dfl sig_err sig_ign sig_setmask sig_unblock sigabrt sigalrm sigbaby sigbus sigchld sigcld sigcont sigfpe sighup sigill sigint sigio sigiot sigkill signeurlpaiement sigpipe sigpoll sigprof sigpwr sigquit sigsegv sigstkflt sigstop sigsys sigterm sigtrap sigtstp sigttin sigttou sigurg sigusr1 sigusr2 sigvtalrm sigwinch sigxcpu sigxfsz similar_text simplexml_import_dom simplexml_load_file simplexml_load_string sin sinh sizeof sleep snmp2_get snmp2_getnext snmp2_real_walk snmp2_set snmp2_walk snmp3_get snmp3_getnext snmp3_real_walk snmp3_set snmp3_walk snmp_bit_str snmp_counter snmp_counter64 snmp_get_quick_print snmp_get_valueretrieval snmp_integer snmp_ipaddress snmp_null snmp_object_id snmp_octet_str snmp_oid_output_full snmp_oid_output_module snmp_oid_output_none snmp_oid_output_numeric snmp_oid_output_suffix snmp_oid_output_ucd snmp_opaque snmp_read_mib snmp_set_enum_print snmp_set_oid_numeric_print snmp_set_oid_output_format snmp_set_quick_print snmp_set_valueretrieval snmp_timeticks snmp_uinteger snmp_unsigned snmp_value_library snmp_value_object snmp_value_plain snmpget snmpgetnext snmprealwalk snmpset snmpwalk snmpwalkoid so_bindtodevice so_broadcast so_debug so_dontroute so_error so_free so_keepalive so_linger so_noserver so_oobinline so_rcvbuf so_rcvlowat so_rcvtimeo so_reuseaddr so_reuseport so_sndbuf so_sndlowat so_sndtimeo so_type soap_1_1 soap_1_2 soap_actor_next soap_actor_none soap_actor_unlimatereceiver soap_authentication_basic soap_authentication_digest soap_compression_accept soap_compression_deflate soap_compression_gzip soap_document soap_enc_array soap_enc_object soap_encoded soap_functions_all soap_literal soap_persistence_request soap_persistence_session soap_rpc soap_single_element_arrays soap_ssl_method_sslv2 soap_ssl_method_sslv23
 soap_ssl_method_sslv3 soap_ssl_method_tls soap_use_xsi_array_type soap_wait_one_way_calls sock_dgram sock_raw sock_rdm sock_seqpacket sock_stream socket_accept socket_addrinuse socket_bind socket_clear_error socket_close socket_cmsg_space socket_connect socket_create socket_create_listen socket_create_pair socket_e2big socket_eacces socket_eaddrinuse socket_eaddrnotavail socket_eadv socket_eafnosupport socket_eagain socket_ealready socket_ebade socket_ebadf socket_ebadfd socket_ebadmsg socket_ebadr socket_ebadrqc socket_ebadslt socket_ebusy socket_echrng socket_ecomm socket_econnaborted socket_econnrefused socket_econnreset socket_edestaddrreq socket_ediscon socket_edquot socket_eduot socket_eexist socket_efault socket_ehostdown socket_ehostunreach socket_eidrm socket_einprogress socket_eintr socket_einval socket_eio socket_eisconn socket_eisdir socket_eisnam socket_el2hlt socket_el2nsync socket_el3hlt socket_el3rst socket_elnrng socket_eloop socket_emediumtype socket_emfile socket_emlink socket_emsgsize socket_emultihop socket_enametoolong socket_enetdown socket_enetreset socket_enetunreach socket_enfile socket_enoano socket_enobufs socket_enocsi socket_enodata socket_enodev socket_enoent socket_enolck socket_enolink socket_enomedium socket_enomem socket_enomsg socket_enonet socket_enoprotoopt socket_enospc socket_enosr socket_enostr socket_enosys socket_enotblk socket_enotconn socket_enotdir socket_enotempty socket_enotsock socket_enotty socket_enotuniq socket_enxio socket_eopnotsupp socket_eperm socket_epfnosupport socket_epipe socket_eproclim socket_eproto socket_eprotonosupport socket_eprotoopt socket_eprototype socket_eremchg socket_eremote socket_eremoteio socket_erestart socket_erofs socket_eshutdown socket_esocktnosupport socket_espipe socket_esrmnt socket_estale socket_estrpipe socket_etime socket_etimedout socket_etoomanyrefs socket_etoomyrefs socket_eunatch socket_eusers socket_ewouldblock socket_exdev socket_exfull socket_get_option socket_get_status socket_getopt socket_getpeername socket_getsockname socket_host_not_found socket_import_stream socket_last_error socket_listen socket_no_address socket_no_data socket_no_recovery socket_notinitialised socket_read socket_recv socket_recvfrom socket_recvmsg socket_select socket_send socket_sendmsg socket_sendto socket_set_block socket_set_blocking socket_set_nonblock socket_set_option socket_set_timeout socket_setopt socket_shutdown socket_strerror socket_sysnotready socket_try_again socket_vernotsupported socket_write sol_socket sol_tcp sol_udp somaxconn sort sort_asc sort_desc sort_flag_case sort_locale_string sort_natural sort_numeric sort_regular sort_string sortarrival sortcc sortdate sortfrom sortsize sortsubject sortto soundex spl_autoload spl_autoload_call spl_autoload_extensions spl_autoload_functions spl_autoload_register spl_autoload_unregister spl_classes spl_object_hash split spliti sprintf sql_best_rowid sql_bigint sql_binary sql_bit sql_char sql_concur_lock sql_concur_read_only sql_concur_rowver sql_concur_values sql_concurrency sql_cur_use_driver sql_cur_use_if_needed sql_cur_use_odbc sql_cursor_dynamic sql_cursor_forward_only sql_cursor_keyset_driven sql_cursor_static sql_cursor_type sql_date sql_decimal sql_double sql_ensure sql_fetch_first sql_fetch_next sql_float sql_index_all sql_index_unique sql_integer sql_keyset_size sql_longvarbinary sql_longvarchar sql_no_nulls sql_nullable sql_numeric sql_odbc_cursors sql_quick sql_real sql_regcase sql_rowver sql_scope_currow sql_scope_session sql_scope_transaction sql_smallint sql_time sql_timestamp sql_tinyint sql_type_date sql_type_time sql_type_timestamp sql_varbinary sql_varchar sql_wchar sql_wlongvarchar sql_wvarchar sqlbit sqlchar sqlflt4 sqlflt8 sqlint1 sqlint2 sqlint4 sqlite3_assoc sqlite3_blob sqlite3_both sqlite3_float sqlite3_integer sqlite3_null sqlite3_num sqlite3_open_create sqlite3_open_readonly sqlite3_open_readwrite sqlite3_text sqlite_abort sqlite_array_query sqlite_assoc sqlite_auth sqlite_both sqlite_busy sqlite_busy_timeout sqlite_cantopen sqlite_changes sqlite_close sqlite_column sqlite_constraint sqlite_corrupt sqlite_create_aggregate sqlite_create_function sqlite_current sqlite_done sqlite_empty sqlite_error sqlite_error_string sqlite_escape_string sqlite_exec sqlite_factory sqlite_fetch_all sqlite_fetch_array sqlite_fetch_column_types sqlite_fetch_object sqlite_fetch_single sqlite_fetch_string sqlite_field_name sqlite_format sqlite_full sqlite_has_more sqlite_has_prev sqlite_internal sqlite_interrupt sqlite_ioerr sqlite_key sqlite_last_error sqlite_last_insert_rowid sqlite_libencoding sqlite_libversion sqlite_locked sqlite_mismatch sqlite_misuse sqlite_next sqlite_nolfs sqlite_nomem sqlite_notadb sqlite_notfound sqlite_num sqlite_num_fields sqlite_num_rows sqlite_ok sqlite_open sqlite_perm sqlite_popen sqlite_prev sqlite_protocol sqlite_query sqlite_readonly sqlite_rewind sqlite_row sqlite_schema sqlite_seek sqlite_single_query sqlite_toobig sqlite_udf_decode_binary sqlite_udf_encode_binary sqlite_unbuffered_query sqlite_valid sqlsrv_begin_transaction sqlsrv_cancel sqlsrv_client_info sqlsrv_close sqlsrv_commit sqlsrv_configure sqlsrv_connect sqlsrv_cursor_buffered sqlsrv_cursor_dynamic sqlsrv_cursor_forward sqlsrv_cursor_keyset sqlsrv_cursor_static sqlsrv_enc_binary sqlsrv_enc_char sqlsrv_err_all sqlsrv_err_errors sqlsrv_err_warnings sqlsrv_errors sqlsrv_execute sqlsrv_fetch sqlsrv_fetch_array sqlsrv_fetch_assoc sqlsrv_fetch_both sqlsrv_fetch_numeric sqlsrv_fetch_object sqlsrv_field_metadata sqlsrv_free_stmt sqlsrv_get_config sqlsrv_get_field sqlsrv_has_rows sqlsrv_log_severity_all sqlsrv_log_severity_error sqlsrv_log_severity_notice sqlsrv_log_severity_warning sqlsrv_log_system_all sqlsrv_log_system_conn sqlsrv_log_system_init sqlsrv_log_system_off sqlsrv_log_system_stmt sqlsrv_log_system_util sqlsrv_next_result sqlsrv_nullable_no sqlsrv_nullable_unknown sqlsrv_nullable_yes sqlsrv_num_fields sqlsrv_num_rows sqlsrv_param_in sqlsrv_param_inout sqlsrv_param_out sqlsrv_phptype_datetime sqlsrv_phptype_float sqlsrv_phptype_int sqlsrv_phptype_null sqlsrv_phptype_stream sqlsrv_phptype_string sqlsrv_prepare sqlsrv_query sqlsrv_rollback sqlsrv_rows_affected sqlsrv_scroll_absolute sqlsrv_scroll_first sqlsrv_scroll_last sqlsrv_scroll_next sqlsrv_scroll_prior sqlsrv_scroll_relative sqlsrv_send_stream_data sqlsrv_server_info sqlsrv_sqltype_bigint sqlsrv_sqltype_binary sqlsrv_sqltype_bit sqlsrv_sqltype_char sqlsrv_sqltype_date sqlsrv_sqltype_datetime sqlsrv_sqltype_datetime2 sqlsrv_sqltype_datetimeoffset sqlsrv_sqltype_decimal sqlsrv_sqltype_float sqlsrv_sqltype_image sqlsrv_sqltype_int sqlsrv_sqltype_money sqlsrv_sqltype_nchar sqlsrv_sqltype_ntext sqlsrv_sqltype_numeric sqlsrv_sqltype_nvarchar sqlsrv_sqltype_real sqlsrv_sqltype_smalldatetime sqlsrv_sqltype_smallint sqlsrv_sqltype_smallmoney sqlsrv_sqltype_text sqlsrv_sqltype_time sqlsrv_sqltype_timestamp sqlsrv_sqltype_tinyint sqlsrv_sqltype_udt sqlsrv_sqltype_uniqueidentifier sqlsrv_sqltype_varbinary sqlsrv_sqltype_varchar sqlsrv_sqltype_xml sqlsrv_txn_read_committed sqlsrv_txn_read_serializable sqlsrv_txn_read_uncommitted sqlsrv_txn_repeatable_read sqlsrv_txn_serializable sqlsrv_txn_snapshot sqlt_afc sqlt_avc sqlt_bdouble sqlt_bfilee sqlt_bfloat sqlt_bin sqlt_blob sqlt_bol sqlt_cfilee sqlt_chr sqlt_clob sqlt_flt sqlt_int sqlt_lbi sqlt_lng sqlt_lvc sqlt_nty sqlt_num sqlt_odt sqlt_rdd sqlt_rset sqlt_str sqlt_uin sqlt_vcs sqltext sqlvarchar sqrt srand sscanf ssdeep_fuzzy_compare ssdeep_fuzzy_hash ssdeep_fuzzy_hash_filename ssh2_auth_agent ssh2_auth_hostbased_file ssh2_auth_none ssh2_auth_password ssh2_auth_pubkey_file ssh2_connect ssh2_default_term_height ssh2_default_term_unit ssh2_default_term_width ssh2_default_terminal ssh2_exec ssh2_fetch_stream ssh2_fingerprint ssh2_fingerprint_hex ssh2_fingerprint_md5 ssh2_fingerprint_raw ssh2_fingerprint_sha1 ssh2_methods_negotiated ssh2_publickey_add ssh2_publickey_init ssh2_publickey_list ssh2_publickey_remove ssh2_scp_recv ssh2_scp_send ssh2_sftp ssh2_sftp_chmod ssh2_sftp_lstat ssh2_sftp_mkdir ssh2_sftp_readlink ssh2_sftp_realpath ssh2_sftp_rename ssh2_sftp_rmdir ssh2_sftp_stat ssh2_sftp_symlink ssh2_sftp_unlink ssh2_shell ssh2_stream_stderr ssh2_stream_stdio ssh2_term_unit_chars ssh2_term_unit_pixels ssh2_tunnel st_set st_silent st_uid stat statement_trace static stats_absolute_deviation stats_cdf_beta stats_cdf_binomial stats_cdf_cauchy stats_cdf_chisquare stats_cdf_exponential stats_cdf_f stats_cdf_gamma stats_cdf_laplace stats_cdf_logistic stats_cdf_negative_binomial stats_cdf_noncentral_chisquare stats_cdf_noncentral_f stats_cdf_poisson stats_cdf_t stats_cdf_uniform stats_cdf_weibull stats_covariance stats_den_uniform stats_dens_beta stats_dens_cauchy stats_dens_chisquare stats_dens_exponential stats_dens_f stats_dens_gamma stats_dens_laplace stats_dens_logistic stats_dens_negative_binomial stats_dens_normal stats_dens_pmf_binomial stats_dens_pmf_hypergeometric stats_dens_pmf_poisson stats_dens_t stats_dens_weibull stats_harmonic_mean stats_kurtosis stats_rand_gen_beta stats_rand_gen_chisquare stats_rand_gen_exponential stats_rand_gen_f stats_rand_gen_funiform stats_rand_gen_gamma stats_rand_gen_ibinomial stats_rand_gen_ibinomial_negative stats_rand_gen_int stats_rand_gen_ipoisson stats_rand_gen_iuniform stats_rand_gen_noncenral_chisquare stats_rand_gen_noncentral_f stats_rand_gen_noncentral_t stats_rand_gen_normal stats_rand_gen_t stats_rand_get_seeds stats_rand_phrase_to_seeds stats_rand_ranf stats_rand_setall stats_skew stats_standard_deviation stats_stat_binomial_coef stats_stat_correlation stats_stat_gennch stats_stat_independent_t stats_stat_innerproduct stats_stat_noncentral_t stats_stat_paired_t stats_stat_percentile stats_stat_powersum stats_variance stdclass str_getcsv
 str_ireplace str_pad str_pad_both str_pad_left str_pad_right str_repeat str_replace str_rot13 str_shuffle str_split str_word_count strcasecmp strchr strcmp strcoll strcspn stream_bucket_append stream_bucket_make_writeable stream_bucket_new stream_bucket_prepend stream_buffer_full stream_buffer_line stream_buffer_none stream_cast_as_stream stream_cast_for_select stream_client_async_connect stream_client_connect stream_client_persistent stream_context_create stream_context_get_default stream_context_get_options stream_context_get_params stream_context_set_default stream_context_set_option stream_context_set_params stream_copy_to_stream stream_crypto_method_any_client stream_crypto_method_any_server stream_crypto_method_sslv23_client stream_crypto_method_sslv23_server stream_crypto_method_sslv2_client stream_crypto_method_sslv2_server stream_crypto_method_sslv3_client stream_crypto_method_sslv3_server stream_crypto_method_tls_client stream_crypto_method_tls_server stream_crypto_method_tlsv1_0_client stream_crypto_method_tlsv1_0_server stream_crypto_method_tlsv1_1_client stream_crypto_method_tlsv1_1_server stream_crypto_method_tlsv1_2_client stream_crypto_method_tlsv1_2_server stream_encoding stream_enforce_safe_mode stream_filter_all stream_filter_append stream_filter_prepend stream_filter_read stream_filter_register stream_filter_remove stream_filter_write stream_get_contents stream_get_filters stream_get_line stream_get_meta_data stream_get_transports stream_get_wrappers stream_ignore_url stream_ipproto_icmp stream_ipproto_ip stream_ipproto_raw stream_ipproto_tcp stream_ipproto_udp stream_is_local stream_is_url stream_meta_access stream_meta_group stream_meta_group_name stream_meta_owner stream_meta_owner_name stream_meta_touch stream_mkdir_recursive stream_must_seek stream_notification_callback stream_notify_auth_required stream_notify_auth_result stream_notify_completed stream_notify_connect stream_notify_failure stream_notify_file_size_is stream_notify_mime_type_is stream_notify_progress stream_notify_redirected stream_notify_resolve stream_notify_severity_err stream_notify_severity_info stream_notify_severity_warn stream_oob stream_option_blocking stream_option_read_buffer stream_option_read_timeout stream_option_write_buffer stream_peek stream_pf_inet stream_pf_inet6 stream_pf_unix stream_register_wrapper stream_report_errors stream_resolve_include_path stream_select stream_server_bind stream_server_listen stream_set_blocking stream_set_chunk_size stream_set_read_buffer stream_set_timeout stream_set_write_buffer stream_shut_rd stream_shut_rdwr stream_shut_wr stream_sock_dgram stream_sock_raw stream_sock_rdm stream_sock_seqpacket stream_sock_stream stream_socket_accept stream_socket_client stream_socket_enable_crypto stream_socket_get_name stream_socket_pair stream_socket_recvfrom stream_socket_sendto stream_socket_server stream_socket_shutdown stream_supports_lock stream_url_stat_link stream_url_stat_quiet stream_use_path stream_wrapper_register stream_wrapper_restore stream_wrapper_unregister strftime string strip_tags stripcslashes stripos stripslashes stristr strlen strnatcasecmp strnatcmp strncasecmp strncmp strpbrk strpos strptime strrchr strrev strripos strrpos strspn strstr strtok strtolower strtotime strtoupper strtr strval substr substr_compare substr_count substr_replace suhosin_patch suhosin_patch_version summary_trace sunfuncs_ret_double sunfuncs_ret_string sunfuncs_ret_timestamp svn_add svn_auth_get_parameter svn_auth_param_config svn_auth_param_config_dir svn_auth_param_default_password svn_auth_param_default_username svn_auth_param_dont_store_passwords svn_auth_param_no_auth_cache svn_auth_param_non_interactive svn_auth_param_server_group svn_auth_param_ssl_server_cert_info svn_auth_param_ssl_server_failures svn_auth_set_parameter svn_blame svn_cat svn_checkout svn_cleanup svn_client_version svn_commit svn_delete svn_diff svn_export svn_fs_abort_txn svn_fs_apply_text svn_fs_begin_txn2 svn_fs_change_node_prop svn_fs_check_path svn_fs_config_fs_type svn_fs_contents_changed svn_fs_copy svn_fs_delete svn_fs_dir_entries svn_fs_file_contents svn_fs_file_length svn_fs_is_dir svn_fs_is_file svn_fs_make_dir svn_fs_make_file svn_fs_node_created_rev svn_fs_node_prop svn_fs_props_changed svn_fs_revision_prop svn_fs_revision_root svn_fs_txn_root svn_fs_type_bdb svn_fs_type_fsfs svn_fs_youngest_rev svn_import svn_log svn_ls svn_mkdir svn_node_dir svn_node_file svn_node_none svn_node_unknown svn_prop_revision_author svn_prop_revision_date svn_prop_revision_log svn_prop_revision_orig_date svn_repos_create svn_repos_fs svn_repos_fs_begin_txn_for_commit svn_repos_fs_commit_txn svn_repos_hotcopy svn_repos_open svn_repos_recover svn_revert svn_revision_head svn_status svn_update svn_wc_status_added svn_wc_status_conflicted svn_wc_status_deleted svn_wc_status_external svn_wc_status_ignored svn_wc_status_incomplete svn_wc_status_merged svn_wc_status_missing svn_wc_status_modified svn_wc_status_none svn_wc_status_normal svn_wc_status_obstructed svn_wc_status_replaced svn_wc_status_unversioned swfaction_data swfaction_enterframe swfaction_keydown swfaction_keyup swfaction_mousedown swfaction_mousemove swfaction_mouseup swfaction_onload swfaction_unload swfbutton_down swfbutton_dragout swfbutton_dragover swfbutton_hit swfbutton_mousedown swfbutton_mouseout swfbutton_mouseover swfbutton_mouseup swfbutton_mouseupoutside swfbutton_over swfbutton_up swffill_clipped_bitmap swffill_linear_gradient swffill_radial_gradient swffill_tiled_bitmap swftextfield_align_center swftextfield_align_justify swftextfield_align_left swftextfield_align_right swftextfield_drawbox swftextfield_haslength swftextfield_html swftextfield_multiline swftextfield_noedit swftextfield_noselect swftextfield_password swftextfield_wordwrap switch sybase_affected_rows sybase_close sybase_connect sybase_data_seek sybase_deadlock_retry_count sybase_fetch_array sybase_fetch_assoc sybase_fetch_field sybase_fetch_object sybase_fetch_row sybase_field_seek sybase_free_result sybase_get_last_message sybase_min_client_severity sybase_min_error_severity sybase_min_message_severity sybase_min_server_severity sybase_num_fields sybase_num_rows sybase_pconnect sybase_query sybase_result sybase_select_db sybase_set_message_handler sybase_unbuffered_query symlink sys_get_temp_dir sys_getloadavg syslog system t_abstract t_and_equal t_array t_array_cast t_as t_bad_character t_bool_cast t_boolean_and t_boolean_or t_break t_callable t_case t_catch t_character t_class t_class_c t_clone t_close_tag t_comment t_concat_equal t_const t_constant_encapsed_string t_continue t_curly_open t_dec t_declare t_default t_dir t_div_equal t_dnumber t_do t_doc_comment t_dollar_open_curly_braces t_double_arrow t_double_cast t_double_colon t_echo t_ellipsis t_else t_elseif t_empty t_encapsed_and_whitespace t_end_heredoc t_enddeclare t_endfor t_endforeach t_endif t_endswitch t_endwhile t_eval t_exit t_extends t_file t_final t_finally t_fmt t_fmt_ampm t_for t_foreach t_func_c t_function t_global t_goto t_halt_compiler t_if t_implements t_inc t_include t_include_once t_inline_html t_instanceof t_insteadof t_int_cast t_interface t_is_equal t_is_greater_or_equal t_is_identical t_is_not_equal t_is_not_identical t_is_smaller_or_equal t_isset t_line t_list t_lnumber t_logical_and t_logical_or t_logical_xor t_method_c t_minus_equal t_mod_equal t_mul_equal t_namespace t_new t_ns_c t_ns_separator t_num_string t_object_cast t_object_operator t_open_tag t_open_tag_with_echo t_or_equal t_paamayim_nekudotayim t_plus_equal t_pow t_pow_equal t_print t_private t_protected t_public t_require t_require_once t_return t_sl t_sl_equal t_sr t_sr_equal t_start_heredoc t_static t_string t_string_cast t_string_varname t_switch t_throw t_trait t_trait_c t_try t_unset t_unset_cast t_use t_var t_variable t_while t_whitespace t_xor_equal t_yield taint tan tanh tcp_nodelay tcpwrap_check tempnam textdomain thousands_sep thousep throw tidy_access_count tidy_clean_repair tidy_config_count tidy_diagnose tidy_error_count tidy_get_body tidy_get_config tidy_get_error_buffer tidy_get_head tidy_get_html tidy_get_html_ver tidy_get_output tidy_get_release tidy_get_root tidy_get_status tidy_getopt tidy_is_xhtml tidy_is_xml tidy_load_config tidy_nodetype_asp tidy_nodetype_cdata tidy_nodetype_comment tidy_nodetype_doctype tidy_nodetype_end tidy_nodetype_jste tidy_nodetype_php tidy_nodetype_procins tidy_nodetype_root tidy_nodetype_section tidy_nodetype_start tidy_nodetype_startend tidy_nodetype_text tidy_nodetype_xmldecl tidy_parse_file tidy_parse_string tidy_repair_file tidy_repair_string tidy_reset_config tidy_save_config tidy_set_encoding tidy_setopt tidy_tag_a tidy_tag_abbr tidy_tag_acronym tidy_tag_address tidy_tag_align tidy_tag_applet tidy_tag_area tidy_tag_b tidy_tag_base tidy_tag_basefont tidy_tag_bdo tidy_tag_bgsound tidy_tag_big tidy_tag_blink tidy_tag_blockquote tidy_tag_body tidy_tag_br tidy_tag_button tidy_tag_caption tidy_tag_center tidy_tag_cite tidy_tag_code tidy_tag_col tidy_tag_colgroup tidy_tag_comment tidy_tag_dd tidy_tag_del tidy_tag_dfn tidy_tag_dir tidy_tag_div tidy_tag_dl tidy_tag_dt tidy_tag_em tidy_tag_embed tidy_tag_fieldset tidy_tag_font tidy_tag_form tidy_tag_frame tidy_tag_frameset tidy_tag_h1 tidy_tag_h2 tidy_tag_h3 tidy_tag_h4 tidy_tag_h5 tidy_tag_h6 tidy_tag_head tidy_tag_hr tidy_tag_html tidy_tag_i tidy_tag_iframe tidy_tag_ilayer tidy_tag_img tidy_tag_input tidy_tag_ins tidy_tag_isindex tidy_tag_kbd tidy_tag_keygen tidy_tag_label tidy_tag_layer tidy_tag_legend tidy_tag_li tidy_tag_link tidy_tag_listing tidy_tag_map tidy_tag_marquee tidy_tag_menu tidy_tag_meta tidy_tag_multicol tidy_tag_nobr tidy_tag_noembed tidy_tag_noframes tidy_tag_nolayer tidy_tag_nosave tidy_tag_noscript tidy_tag_object tidy_tag_ol
 tidy_tag_optgroup tidy_tag_option tidy_tag_p tidy_tag_param tidy_tag_plaintext tidy_tag_pre tidy_tag_q tidy_tag_rb tidy_tag_rbc tidy_tag_rp tidy_tag_rt tidy_tag_rtc tidy_tag_ruby tidy_tag_s tidy_tag_samp tidy_tag_script tidy_tag_select tidy_tag_server tidy_tag_servlet tidy_tag_small tidy_tag_spacer tidy_tag_span tidy_tag_strike tidy_tag_strong tidy_tag_style tidy_tag_sub tidy_tag_sup tidy_tag_table tidy_tag_tbody tidy_tag_td tidy_tag_textarea tidy_tag_tfoot tidy_tag_th tidy_tag_thead tidy_tag_title tidy_tag_tr tidy_tag_tt tidy_tag_u tidy_tag_ul tidy_tag_unknown tidy_tag_var tidy_tag_wbr tidy_tag_xmp tidy_warning_count time time_nanosleep time_sleep_until timezone_abbreviations_list timezone_identifiers_list timezone_location_get timezone_name_from_abbr timezone_name_get timezone_offset_get timezone_open timezone_transitions_get timezone_version_get timing_trace tmpfile token_get_all token_name touch trader_acos trader_ad trader_add trader_adosc trader_adx trader_adxr trader_apo trader_aroon trader_aroonosc trader_asin trader_atan trader_atr trader_avgprice trader_bbands trader_beta trader_bop trader_cci trader_cdl2crows trader_cdl3blackcrows trader_cdl3inside trader_cdl3linestrike trader_cdl3outside trader_cdl3starsinsouth trader_cdl3whitesoldiers trader_cdlabandonedbaby trader_cdladvanceblock trader_cdlbelthold trader_cdlbreakaway trader_cdlclosingmarubozu trader_cdlconcealbabyswall trader_cdlcounterattack trader_cdldarkcloudcover trader_cdldoji trader_cdldojistar trader_cdldragonflydoji trader_cdlengulfing trader_cdleveningdojistar trader_cdleveningstar trader_cdlgapsidesidewhite trader_cdlgravestonedoji trader_cdlhammer trader_cdlhangingman trader_cdlharami trader_cdlharamicross trader_cdlhighwave trader_cdlhikkake trader_cdlhikkakemod trader_cdlhomingpigeon trader_cdlidentical3crows trader_cdlinneck trader_cdlinvertedhammer trader_cdlkicking trader_cdlkickingbylength trader_cdlladderbottom trader_cdllongleggeddoji trader_cdllongline trader_cdlmarubozu trader_cdlmatchinglow trader_cdlmathold trader_cdlmorningdojistar trader_cdlmorningstar trader_cdlonneck trader_cdlpiercing trader_cdlrickshawman trader_cdlrisefall3methods trader_cdlseparatinglines trader_cdlshootingstar trader_cdlshortline trader_cdlspinningtop trader_cdlstalledpattern trader_cdlsticksandwich trader_cdltakuri trader_cdltasukigap trader_cdlthrusting trader_cdltristar trader_cdlunique3river trader_cdlupsidegap2crows trader_cdlxsidegap3methods trader_ceil trader_cmo trader_compatibility_default trader_compatibility_metastock trader_correl trader_cos trader_cosh trader_dema trader_div trader_dx trader_ema trader_err_alloc_err trader_err_bad_object trader_err_bad_param trader_err_func_not_found trader_err_group_not_found trader_err_input_not_all_initialize trader_err_internal_error trader_err_invalid_handle trader_err_invalid_list_type trader_err_invalid_param_function trader_err_invalid_param_holder trader_err_invalid_param_holder_type trader_err_lib_not_initialize trader_err_not_supported trader_err_out_of_range_end_index trader_err_out_of_range_start_index trader_err_output_not_all_initialize trader_err_success trader_err_unknown_error trader_errno trader_exp trader_floor trader_func_unst_adx trader_func_unst_adxr trader_func_unst_all trader_func_unst_atr trader_func_unst_cmo trader_func_unst_dx trader_func_unst_ema trader_func_unst_ht_dcperiod trader_func_unst_ht_dcphase trader_func_unst_ht_phasor trader_func_unst_ht_sine trader_func_unst_ht_trendline trader_func_unst_ht_trendmode trader_func_unst_kama trader_func_unst_mama trader_func_unst_mfi trader_func_unst_minus_di trader_func_unst_minus_dm trader_func_unst_natr trader_func_unst_none trader_func_unst_plus_di trader_func_unst_plus_dm trader_func_unst_rsi trader_func_unst_stochrsi trader_func_unst_t3 trader_get_compat trader_get_unstable_period trader_ht_dcperiod trader_ht_dcphase trader_ht_phasor trader_ht_sine trader_ht_trendline trader_ht_trendmode trader_kama trader_linearreg trader_linearreg_angle trader_linearreg_intercept trader_linearreg_slope trader_ln trader_log10 trader_ma trader_ma_type_dema trader_ma_type_ema trader_ma_type_kama trader_ma_type_mama trader_ma_type_sma trader_ma_type_t3 trader_ma_type_tema trader_ma_type_trima trader_ma_type_wma trader_macd trader_macdext trader_macdfix trader_mama trader_mavp trader_max trader_maxindex trader_medprice trader_mfi trader_midpoint trader_midprice trader_min trader_minindex trader_minmax trader_minmaxindex trader_minus_di trader_minus_dm trader_mom trader_mult trader_natr trader_obv trader_plus_di trader_plus_dm trader_ppo trader_real_max trader_real_min trader_roc trader_rocp trader_rocr trader_rocr100 trader_rsi trader_sar trader_sarext trader_set_compat trader_set_unstable_period trader_sin trader_sinh trader_sma trader_sqrt trader_stddev trader_stoch trader_stochf trader_stochrsi trader_sub trader_sum trader_t3 trader_tan trader_tanh trader_tema trader_trange trader_trima trader_trix trader_tsf trader_typprice trader_ultosc trader_var trader_wclprice trader_willr trader_wma trait trait_exists tran_commit_class_commit_instance tran_commit_class_uncommit_instance tran_rep_class_commit_instance tran_rep_class_rep_instance tran_rep_class_uncommit_instance tran_serializable transliterator_create transliterator_create_from_rules transliterator_create_inverse transliterator_get_error_code transliterator_get_error_message transliterator_list_ids transliterator_transliterate trap_brkpt trap_trace trigger_error trim true try typeapplication typeaudio typeimage typemessage typemodel typemultipart typeother typetext typevideo u_ambiguous_alias_warning u_bad_variable_definition u_brk_assign_error u_brk_error_limit u_brk_error_start u_brk_hex_digits_expected u_brk_init_error u_brk_internal_error u_brk_malformed_rule_tag u_brk_mismatched_paren u_brk_new_line_in_quoted_string u_brk_rule_empty_set u_brk_rule_syntax u_brk_semicolon_expected u_brk_unclosed_set u_brk_undefined_variable u_brk_unrecognized_option u_brk_variable_redfinition u_buffer_overflow_error u_ce_not_found_error u_collator_version_mismatch u_different_uca_version u_enum_out_of_sync_error u_error_limit u_error_warning_limit u_error_warning_start u_file_access_error u_fmt_parse_error_limit u_fmt_parse_error_start u_idna_ace_prefix_error u_idna_check_bidi_error u_idna_domain_name_too_long_error u_idna_error_limit u_idna_error_start u_idna_label_too_long_error u_idna_prohibited_error u_idna_std3_ascii_rules_error u_idna_unassigned_error u_idna_verification_error u_idna_zero_length_label_error u_illegal_argument_error u_illegal_char_found u_illegal_char_in_segment u_illegal_character u_illegal_escape_sequence u_illegal_pad_position u_index_outofbounds_error u_internal_program_error u_internal_transliterator_error u_invalid_char_found u_invalid_format_error u_invalid_function u_invalid_id u_invalid_property_pattern u_invalid_rbt_syntax u_invalid_state_error u_invalid_table_file u_invalid_table_format u_invariant_conversion_error u_malformed_exponential_pattern u_malformed_pragma u_malformed_rule u_malformed_set u_malformed_symbol_reference u_malformed_unicode_escape u_malformed_variable_definition u_malformed_variable_reference u_memory_allocation_error u_message_parse_error u_mismatched_segment_delimiters u_misplaced_anchor_start u_misplaced_compound_filter u_misplaced_cursor_offset u_misplaced_quantifier u_missing_operator u_missing_resource_error u_missing_segment_close u_multiple_ante_contexts u_multiple_compound_filters u_multiple_cursors u_multiple_decimal_separators u_multiple_decimal_seperators u_multiple_exponential_symbols u_multiple_pad_specifiers u_multiple_percent_symbols u_multiple_permill_symbols u_multiple_post_contexts u_no_space_available u_no_write_permission u_parse_error u_parse_error_limit u_parse_error_start u_pattern_syntax_error u_primary_too_long_error u_regex_bad_escape_sequence u_regex_bad_interval u_regex_error_limit u_regex_error_start u_regex_internal_error u_regex_invalid_back_ref u_regex_invalid_flag u_regex_invalid_state u_regex_look_behind_limit u_regex_max_lt_min u_regex_mismatched_paren u_regex_number_too_big u_regex_property_syntax u_regex_rule_syntax u_regex_set_contains_string u_regex_unimplemented u_resource_type_mismatch u_rule_mask_error u_safeclone_allocated_warning u_sort_key_too_short_warning u_standard_error_limit u_state_old_warning u_state_too_old_error u_string_not_terminated_warning u_stringprep_check_bidi_error u_stringprep_prohibited_error u_stringprep_unassigned_error u_too_many_aliases_error u_trailing_backslash u_truncated_char_found u_unclosed_segment u_undefined_segment_reference u_undefined_variable u_unexpected_token u_unmatched_braces u_unquoted_special u_unsupported_attribute u_unsupported_error u_unsupported_escape_sequence u_unsupported_property u_unterminated_quote u_useless_collator_error u_using_default_warning u_using_fallback_warning u_variable_range_exhausted u_variable_range_overlap u_zero_error uasort ucfirst ucwords udm_add_search_limit udm_alloc_agent udm_alloc_agent_array udm_api_version udm_cat_list udm_cat_path udm_check_charset udm_clear_search_limits udm_crc32 udm_errno udm_error udm_find udm_free_agent udm_free_ispell_data udm_free_res udm_get_doc_count udm_get_res_field udm_get_res_param udm_hash32 udm_load_ispell_data udm_set_agent_param uksort uloc_actual_locale uloc_valid_locale umask uniqid unixtojd unknown_type unlink unpack unregister_tick_function unserialize unset untaint upload_err_cant_write upload_err_extension upload_err_form_size upload_err_ini_size upload_err_no_file upload_err_no_tmp_dir upload_err_ok upload_err_partial urldecode urlencode use use_soap_error_handler user_error usleep usort utf8_decode utf8_encode var var_dump var_export varcmp_eq varcmp_gt varcmp_lt varcmp_null variant_abs
 variant_add variant_and variant_cast variant_cat variant_cmp variant_date_from_timestamp variant_date_to_timestamp variant_div variant_eqv variant_fix variant_get_type variant_idiv variant_imp variant_int variant_mod variant_mul variant_neg variant_not variant_or variant_pow variant_round variant_set variant_set_type variant_sub variant_xor version_compare vfprintf virtual void vpopmail_add_alias_domain vpopmail_add_alias_domain_ex vpopmail_add_domain vpopmail_add_domain_ex vpopmail_add_user vpopmail_alias_add vpopmail_alias_del vpopmail_alias_del_domain vpopmail_alias_get vpopmail_alias_get_all vpopmail_auth_user vpopmail_del_domain vpopmail_del_domain_ex vpopmail_del_user vpopmail_error vpopmail_passwd vpopmail_set_user_quota vprintf vsprintf vt_array vt_bool vt_bstr vt_byref vt_cy vt_date vt_decimal vt_dispatch vt_empty vt_error vt_i1 vt_i2 vt_i4 vt_int vt_null vt_r4 vt_r8 vt_ui1 vt_ui2 vt_ui4 vt_uint vt_unknown vt_variant wddx_add_vars wddx_deserialize wddx_packet_end wddx_packet_start wddx_serialize_value wddx_serialize_vars while win32_above_normal_priority_class win32_below_normal_priority_class win32_continue_service win32_create_service win32_delete_service win32_error_access_denied win32_error_circular_dependency win32_error_database_does_not_exist win32_error_dependent_services_running win32_error_duplicate_service_name win32_error_failed_service_controller_connect win32_error_insufficient_buffer win32_error_invalid_data win32_error_invalid_handle win32_error_invalid_level win32_error_invalid_name win32_error_invalid_parameter win32_error_invalid_service_account win32_error_invalid_service_control win32_error_path_not_found win32_error_service_already_running win32_error_service_cannot_accept_ctrl win32_error_service_database_locked win32_error_service_dependency_deleted win32_error_service_dependency_fail win32_error_service_disabled win32_error_service_does_not_exist win32_error_service_exists win32_error_service_logon_failed win32_error_service_marked_for_delete win32_error_service_no_thread win32_error_service_not_active win32_error_service_request_timeout win32_error_shutdown_in_progress win32_get_last_control_message win32_high_priority_class win32_idle_priority_class win32_no_error win32_normal_priority_class win32_pause_service win32_ps_list_procs win32_ps_stat_mem win32_ps_stat_proc win32_query_service_status win32_realtime_priority_class win32_service_accept_pause_continue win32_service_accept_preshutdown win32_service_accept_shutdown win32_service_accept_stop win32_service_auto_start win32_service_continue_pending win32_service_control_continue win32_service_control_interrogate win32_service_control_pause win32_service_control_preshutdown win32_service_control_shutdown win32_service_control_stop win32_service_demand_start win32_service_disabled win32_service_error_ignore win32_service_error_normal win32_service_interactive_process win32_service_pause_pending win32_service_paused win32_service_running win32_service_runs_in_system_process win32_service_start_pending win32_service_stop_pending win32_service_stopped win32_service_win32_own_process win32_service_win32_own_process_interactive win32_set_service_status win32_start_service win32_start_service_ctrl_dispatcher win32_stop_service wincache_fcache_fileinfo wincache_fcache_meminfo wincache_lock wincache_ocache_fileinfo wincache_ocache_meminfo wincache_refresh_if_changed wincache_rplist_fileinfo wincache_rplist_meminfo wincache_scache_info wincache_scache_meminfo wincache_ucache_add wincache_ucache_cas wincache_ucache_clear wincache_ucache_dec wincache_ucache_delete wincache_ucache_exists wincache_ucache_get wincache_ucache_inc wincache_ucache_info wincache_ucache_meminfo wincache_ucache_set wincache_unlock wnohang wordwrap wsdl_cache_both wsdl_cache_disk wsdl_cache_memory wsdl_cache_none wuntraced x509_purpose_any x509_purpose_crl_sign x509_purpose_ns_ssl_server x509_purpose_smime_encrypt x509_purpose_smime_sign x509_purpose_ssl_client x509_purpose_ssl_server xattr_create xattr_dontfollow xattr_get xattr_list xattr_remove xattr_replace xattr_root xattr_set xattr_supported xdiff_file_bdiff xdiff_file_bdiff_size xdiff_file_bpatch xdiff_file_diff xdiff_file_diff_binary xdiff_file_merge3 xdiff_file_patch xdiff_file_patch_binary xdiff_file_rabdiff xdiff_patch_normal xdiff_patch_reverse xdiff_string_bdiff xdiff_string_bdiff_size xdiff_string_bpatch xdiff_string_diff xdiff_string_diff_binary xdiff_string_merge3 xdiff_string_patch xdiff_string_patch_binary xdiff_string_rabdiff xhprof_disable xhprof_enable xhprof_sample_disable xhprof_sample_enable xml_attribute_cdata xml_attribute_decl_node xml_attribute_entity xml_attribute_enumeration xml_attribute_id xml_attribute_idref xml_attribute_idrefs xml_attribute_nmtoken xml_attribute_nmtokens xml_attribute_node xml_attribute_notation xml_cdata_section_node xml_comment_node xml_document_frag_node xml_document_node xml_document_type_node xml_dtd_node xml_element_decl_node xml_element_node xml_entity_decl_node xml_entity_node xml_entity_ref_node xml_error_async_entity xml_error_attribute_external_entity_ref xml_error_bad_char_ref xml_error_binary_entity_ref xml_error_duplicate_attribute xml_error_external_entity_handling xml_error_incorrect_encoding xml_error_invalid_token xml_error_junk_after_doc_element xml_error_misplaced_xml_pi xml_error_no_elements xml_error_no_memory xml_error_none xml_error_param_entity_ref xml_error_partial_char xml_error_recursive_entity_ref xml_error_string xml_error_syntax xml_error_tag_mismatch xml_error_unclosed_cdata_section xml_error_unclosed_token xml_error_undefined_entity xml_error_unknown_encoding xml_get_current_byte_index xml_get_current_column_number xml_get_current_line_number xml_get_error_code xml_html_document_node xml_local_namespace xml_namespace_decl_node xml_notation_node xml_option_case_folding xml_option_skip_tagstart xml_option_skip_white xml_option_target_encoding xml_parse xml_parse_into_struct xml_parser_create xml_parser_create_ns xml_parser_free xml_parser_get_option xml_parser_set_option xml_pi_node xml_sax_impl xml_set_character_data_handler xml_set_default_handler xml_set_element_handler xml_set_end_namespace_decl_handler xml_set_external_entity_ref_handler xml_set_notation_decl_handler xml_set_object xml_set_processing_instruction_handler xml_set_start_namespace_decl_handler xml_set_unparsed_entity_decl_handler xml_text_node xmlrpc_decode xmlrpc_decode_request xmlrpc_encode xmlrpc_encode_request xmlrpc_get_type xmlrpc_is_fault xmlrpc_parse_method_descriptions xmlrpc_server_add_introspection_data xmlrpc_server_call_method xmlrpc_server_create xmlrpc_server_destroy xmlrpc_server_register_introspection_callback xmlrpc_server_register_method xmlrpc_set_type xmlwriter_end_attribute xmlwriter_end_cdata xmlwriter_end_comment xmlwriter_end_document xmlwriter_end_dtd xmlwriter_end_dtd_attlist xmlwriter_end_dtd_element xmlwriter_end_dtd_entity xmlwriter_end_element xmlwriter_end_pi xmlwriter_flush xmlwriter_full_end_element xmlwriter_open_memory xmlwriter_open_uri xmlwriter_output_memory xmlwriter_set_indent xmlwriter_set_indent_string xmlwriter_start_attribute xmlwriter_start_attribute_ns xmlwriter_start_cdata xmlwriter_start_comment xmlwriter_start_document xmlwriter_start_dtd xmlwriter_start_dtd_attlist xmlwriter_start_dtd_element xmlwriter_start_dtd_entity xmlwriter_start_element xmlwriter_start_element_ns xmlwriter_start_pi xmlwriter_text xmlwriter_write_attribute xmlwriter_write_attribute_ns xmlwriter_write_cdata xmlwriter_write_comment xmlwriter_write_dtd xmlwriter_write_dtd_attlist xmlwriter_write_dtd_element xmlwriter_write_dtd_entity xmlwriter_write_element xmlwriter_write_element_ns xmlwriter_write_pi xmlwriter_write_raw xor xsd_1999_namespace xsd_1999_timeinstant xsd_anytype xsd_anyuri xsd_anyxml xsd_base64binary xsd_boolean xsd_byte xsd_date xsd_datetime xsd_decimal xsd_double xsd_duration xsd_entities xsd_entity xsd_float xsd_gday xsd_gmonth xsd_gmonthday xsd_gyear xsd_gyearmonth xsd_hexbinary xsd_id xsd_idref xsd_idrefs xsd_int xsd_integer xsd_language xsd_long xsd_name xsd_namespace xsd_ncname xsd_negativeinteger xsd_nmtoken xsd_nmtokens xsd_nonnegativeinteger xsd_nonpositiveinteger xsd_normalizedstring xsd_notation xsd_positiveinteger xsd_qname xsd_short xsd_string xsd_time xsd_token xsd_unsignedbyte xsd_unsignedint xsd_unsignedlong xsd_unsignedshort xsl_clone_always xsl_clone_auto xsl_clone_never xsl_secpref_create_directory xsl_secpref_default xsl_secpref_none xsl_secpref_read_file xsl_secpref_read_network xsl_secpref_write_file xsl_secpref_write_network yaml_any_break yaml_any_encoding yaml_any_scalar_style yaml_bool_tag yaml_cr_break yaml_crln_break yaml_double_quoted_scalar_style yaml_emit yaml_emit_file yaml_float_tag yaml_folded_scalar_style yaml_int_tag yaml_literal_scalar_style yaml_ln_break yaml_map_tag yaml_null_tag yaml_parse yaml_parse_file yaml_parse_url yaml_php_tag yaml_plain_scalar_style yaml_seq_tag yaml_single_quoted_scalar_style yaml_str_tag yaml_timestamp_tag yaml_utf16be_encoding yaml_utf16le_encoding yaml_utf8_encoding yesexpr yesstr yield zend_debug_build zend_logo_guid zend_multibyte zend_thread_id zend_thread_safe zend_version zip_close zip_entry_close zip_entry_compressedsize zip_entry_compressionmethod zip_entry_filesize zip_entry_name zip_entry_open zip_entry_read zip_open zip_read zlib_decode zlib_encode zlib_encoding_deflate zlib_encoding_gzip zlib_encoding_raw zlib_get_coding_type";
// color text
static SScintillaColors g_rgb_Syntax_php[] =
{ {} };

//--------------------------------
//---- postscript Language
//--------------------------------
// language
static CString g_str_postscript_language = _T("postscript");
// extentions
static CString g_str_postscript_extention = _T("postscript");
// comment line
static CString g_str_postscript_commentline = _T("%");
// comment start
static CString g_str_postscript_commentStart = _T("");
// comment end
static CString g_str_postscript_commentEnd = _T("");
// keywords
static const char* g_postscript_KeyWords =
"$error = == FontDirectory StandardEncoding UserObjects abs add aload anchorsearch and arc arcn arcto array ashow astore atan awidthshow begin bind bitshift bytesavailable cachestatus ceiling charpath clear cleardictstack cleartomark clip clippath closefile closepath concat concatmatrix copy copypage cos count countdictstack countexecstack counttomark currentcmykcolor currentcolorspace currentdash currentdict currentfile currentflat currentfont currentgray currenthsbcolor currentlinecap currentlinejoin currentlinewidth currentmatrix currentmiterlimit currentpagedevice currentpoint currentrgbcolor currentscreen currenttransfer cvi cvlit cvn cvr cvrs cvs cvx def defaultmatrix definefont dict dictstack div dtransform dup echo end eoclip eofill eq erasepage errordict exch exec execstack executeonly executive exit exp false file fill findfont flattenpath floor flush flushfile for forall ge get getinterval grestore grestoreall gsave gt idetmatrix idiv idtransform if ifelse image imagemask index initclip initgraphics initmatrix inustroke invertmatrix itransform known kshow le length lineto ln load log loop lt makefont mark matrix maxlength mod moveto mul ne neg newpath noaccess nor not null nulldevice or pathbbox pathforall pop print prompt pstack put putinterval quit rand rcheck rcurveto read readhexstring readline readonly readstring rectstroke repeat resetfile restore reversepath rlineto rmoveto roll rotate round rrand run save scale scalefont search setblackgeneration setcachedevice setcachelimit setcharwidth setcolorscreen setcolortransfer setdash setflat setfont setgray sethsbcolor setlinecap setlinejoin setlinewidth setmatrix setmiterlimit setpagedevice setrgbcolor setscreen settransfer setvmthreshold show showpage sin sqrt srand stack start status statusdict stop stopped store string stringwidth stroke strokepath sub systemdict token transform translate true truncate type ueofill undefineresource userdict usertime version vmstatus wcheck where widthshow write writehexstring writestring xcheck xor"
"GlobalFontDirectory ISOLatin1Encoding SharedFontDirectory UserObject arct colorimage cshow currentblackgeneration currentcacheparams currentcmykcolor currentcolor currentcolorrendering currentcolorscreen currentcolorspace currentcolortransfer currentdevparams currentglobal currentgstate currenthalftone currentobjectformat currentoverprint currentpacking currentpagedevice currentshared currentstrokeadjust currentsystemparams currentundercolorremoval currentuserparams defineresource defineuserobject deletefile execform execuserobject filenameforall fileposition filter findencoding findresource gcheck globaldict glyphshow gstate ineofill infill instroke inueofill inufill inustroke languagelevel makepattern packedarray printobject product realtime rectclip rectfill rectstroke renamefile resourceforall resourcestatus revision rootfont scheck selectfont serialnumber setbbox setblackgeneration setcachedevice2 setcacheparams setcmykcolor setcolor setcolorrendering setcolorscreen setcolorspace setcolortranfer setdevparams setfileposition setglobal setgstate sethalftone setobjectformat setoverprint setpacking setpagedevice setpattern setshared setstrokeadjust setsystemparams setucacheparams setundercolorremoval setuserparams setvmthreshold shareddict startjob uappend ucache ucachestatus ueofill ufill undef undefinefont undefineresource undefineuserobject upath ustroke ustrokepath vmreclaim writeobject xshow xyshow yshow"
"cliprestore clipsave composefont currentsmoothness findcolorrendering setsmoothness shfill"
".begintransparencygroup .begintransparencymask .bytestring .charboxpath .currentaccuratecurves .currentblendmode .currentcurvejoin .currentdashadapt .currentdotlength .currentfilladjust2 .currentlimitclamp .currentopacityalpha .currentoverprintmode .currentrasterop .currentshapealpha .currentsourcetransparent .currenttextknockout .currenttexturetransparent .dashpath .dicttomark .discardtransparencygroup .discardtransparencymask .endtransparencygroup .endtransparencymask .execn .filename .fileposition .forceput .forceundef .forgetsave .getbitsrect .getdevice .inittransparencymask .knownget .locksafe .makeoperator .namestring .oserrno .oserrorstring .peekstring .rectappend .runandhide .setaccuratecurves .setblendmode .setcurvejoin .setdashadapt .setdebug .setdefaultmatrix .setdotlength .setfilladjust2 .setlimitclamp .setmaxlength .setopacityalpha .setoverprintmode .setrasterop .setsafe .setshapealpha .setsourcetransparent .settextknockout .settexturetransparent .stringbreak .stringmatch .tempfile .type1decrypt .type1encrypt .type1execchar .unread arccos arcsin copydevice copyscanlines currentdevice finddevice findlibfile findprotodevice flushpage getdeviceprops getenv makeimagedevice makewordimagedevice max min putdeviceprops setdevice"
".begintransparencygroup .begintransparencymask .bytestring .charboxpath .currentaccuratecurves .currentblendmode .currentcurvejoin .currentdashadapt .currentdotlength .currentfilladjust2 .currentlimitclamp .currentopacityalpha .currentoverprintmode .currentrasterop .currentshapealpha .currentsourcetransparent .currenttextknockout .currenttexturetransparent .dashpath .dicttomark .discardtransparencygroup .discardtransparencymask .endtransparencygroup .endtransparencymask .execn .filename .fileposition .forceput .forceundef .forgetsave .getbitsrect .getdevice .inittransparencymask .knownget .locksafe .makeoperator .namestring .oserrno .oserrorstring .peekstring .rectappend .runandhide .setaccuratecurves .setblendmode .setcurvejoin .setdashadapt .setdebug .setdefaultmatrix .setdotlength .setfilladjust2 .setlimitclamp .setmaxlength .setopacityalpha .setoverprintmode .setrasterop .setsafe .setshapealpha .setsourcetransparent .settextknockout .settexturetransparent .stringbreak .stringmatch .tempfile .type1decrypt .type1encrypt .type1execchar .unread arccos arcsin copydevice copyscanlines currentdevice finddevice findlibfile findprotodevice flushpage getdeviceprops getenv makeimagedevice makewordimagedevice max min putdeviceprops setdevice";
// color text
static SScintillaColors g_rgb_Syntax_postscript[] =
{ {} };

//--------------------------------
//---- powershell Language
//--------------------------------
// language
static CString g_str_powershell_language = _T("powershell");
// extentions
static CString g_str_powershell_extention = _T("powershell");
// comment line
static CString g_str_powershell_commentline = _T("#");
// comment start
static CString g_str_powershell_commentStart = _T("<#");
// comment end
static CString g_str_powershell_commentEnd = _T("#>");
// keywords
static const char* g_powershell_KeyWords =
"break continue do else elseif filter for foreach function if in return switch until where while"
"add-content add-history add-member add-pssnapin clear-content clear-item clear-itemproperty clear-variable compare-object convertfrom-securestring convert-path convertto-html convertto-securestring copy-item copy-itemproperty export-alias export-clixml export-console export-csv foreach-object format-custom format-list format-table format-wide get-acl get-alias get-authenticodesignature get-childitem get-command get-content get-credential get-culture get-date get-eventlog get-executionpolicy get-help get-history get-host get-item get-itemproperty get-location get-member get-pfxcertificate get-process get-psdrive get-psprovider get-pssnapin get-service get-tracesource get-uiculture get-unique get-variable get-wmiobject group-object import-alias import-clixml import-csv invoke-expression invoke-history invoke-item join-path measure-command measure-object move-item move-itemproperty new-alias new-item new-itemproperty new-object new-psdrive new-service new-timespan new-variable out-default out-file out-host out-null out-printer out-string pop-location push-location read-host remove-item remove-itemproperty remove-psdrive remove-pssnapin remove-variable rename-item rename-itemproperty resolve-path restart-service resume-service select-object select-string set-acl set-alias set-authenticodesignature set-content set-date set-executionpolicy set-item set-itemproperty set-location set-psdebug set-service set-tracesource set-variable sort-object split-path start-service start-sleep start-transcript stop-process stop-service stop-transcript suspend-service tee-object test-path trace-command update-formatdata update-typedata where-object write-debug write-error write-host write-output write-progress write-verbose write-warning"
"ac asnp clc cli clp clv cpi cpp cvpa diff epal epcsv fc fl foreach ft fw gal gc gci gcm gdr ghy gi gl gm gp gps group gsv gsnp gu gv gwmi iex ihy ii ipal ipcsv mi mp nal ndr ni nv oh rdr ri rni rnp rp rsnp rv rvpa sal sasv sc select si sl sleep sort sp spps spsv sv tee where write cat cd clear cp h history kill lp ls mount mv popd ps pushd pwd r rm rmdir echo cls chdir copy del dir erase move rd ren set type"
"component description example externalhelp forwardhelpcategory forwardhelptargetname functionality inputs link notes outputs parameter remotehelprunspace role synopsis"
"component description example externalhelp forwardhelpcategory forwardhelptargetname functionality inputs link notes outputs parameter remotehelprunspace role synopsis";
// color text
static SScintillaColors g_rgb_Syntax_powershell[] =
{ {} };

//--------------------------------
//---- props Language
//--------------------------------
// language
static CString g_str_props_language = _T("props");
// extentions
static CString g_str_props_extention = _T("props");
// comment line
static CString g_str_props_commentline = _T(";");
// comment start
static CString g_str_props_commentStart = _T("");
// comment end
static CString g_str_props_commentEnd = _T("");
// keywords
static const char* g_props_KeyWords =
// color text
static SScintillaColors g_rgb_Syntax_props[] =
{ {} };

//--------------------------------
//---- purebasic Language
//--------------------------------
// language
static CString g_str_purebasic_language = _T("purebasic");
// extentions
static CString g_str_purebasic_extention = _T("purebasic");
// comment line
static CString g_str_purebasic_commentline = _T("");
// comment start
static CString g_str_purebasic_commentStart = _T("");
// comment end
static CString g_str_purebasic_commentEnd = _T("");
// keywords
static const char* g_purebasic_KeyWords =
"and break case continue data datasection declare declarecdll declaredll default deftype dim else elseif end enddatasection endenumeration endif endinterface endprocedure endselect endstructure endstructureunion enumeration extends fakereturn for foreach forever global gosub goto if includebinary includefile includepath interface newlist next or procedure procedurecdll proceduredll procedurereturn protected read repeat restore return select shared static step structure structureunion to until wend while xincludefile"
"compilercase compilerdefault compilerelse compilerendif compilerendselect compilerif compilerselect"
""
""
"";
// color text
static SScintillaColors g_rgb_Syntax_purebasic[] =
{ {} };

//--------------------------------
//---- python Language
//--------------------------------
// language
static CString g_str_python_language = _T("python");
// extentions
static CString g_str_python_extention = _T("python");
// comment line
static CString g_str_python_commentline = _T("#");
// comment start
static CString g_str_python_commentStart = _T("");
// comment end
static CString g_str_python_commentEnd = _T("");
// keywords
static const char* g_python_KeyWords =
"and as assert async await break class continue def del elif else except finally for from global if import in is lambda nonlocal not or pass raise return try while with yield"
"ArithmeticError AssertionError AttributeError BaseException BlockingIOError BrokenPipeError BufferError BytesWarning ChildProcessError ConnectionAbortedError ConnectionError ConnectionRefusedError ConnectionResetError DeprecationWarning EOFError Ellipsis EnvironmentError Exception False FileExistsError FileNotFoundError FloatingPointError FutureWarning GeneratorExit IOError ImportError ImportWarning IndentationError IndexError InterruptedError IsADirectoryError KeyError KeyboardInterrupt LookupError MemoryError ModuleNotFoundError NameError None NotADirectoryError NotImplemented NotImplementedError OSError OverflowError PendingDeprecationWarning PermissionError ProcessLookupError RecursionError ReferenceError ResourceWarning RuntimeError RuntimeWarning StopAsyncIteration StopIteration SyntaxError SyntaxWarning SystemError SystemExit TabError TimeoutError True TypeError UnboundLocalError UnicodeDecodeError UnicodeEncodeError UnicodeError UnicodeTranslateError UnicodeWarning UserWarning ValueError Warning WindowsError ZeroDivisionError abs all any ascii bin bool breakpoint bytearray bytes callable chr classmethod compile complex copyright credits delattr dict dir divmod enumerate eval exec exit filter float format frozenset getattr globals hasattr hash help hex id input int isinstance issubclass iter len license list locals map max memoryview min next object oct open ord pow print property quit range repr reversed round set setattr slice sorted staticmethod str sum super tuple type vars zip"
"ArithmeticError AssertionError AttributeError BaseException BlockingIOError BrokenPipeError BufferError BytesWarning ChildProcessError ConnectionAbortedError ConnectionError ConnectionRefusedError ConnectionResetError DeprecationWarning EOFError Ellipsis EnvironmentError Exception False FileExistsError FileNotFoundError FloatingPointError FutureWarning GeneratorExit IOError ImportError ImportWarning IndentationError IndexError InterruptedError IsADirectoryError KeyError KeyboardInterrupt LookupError MemoryError ModuleNotFoundError NameError None NotADirectoryError NotImplemented NotImplementedError OSError OverflowError PendingDeprecationWarning PermissionError ProcessLookupError RecursionError ReferenceError ResourceWarning RuntimeError RuntimeWarning StopAsyncIteration StopIteration SyntaxError SyntaxWarning SystemError SystemExit TabError TimeoutError True TypeError UnboundLocalError UnicodeDecodeError UnicodeEncodeError UnicodeError UnicodeTranslateError UnicodeWarning UserWarning ValueError Warning WindowsError ZeroDivisionError abs all any ascii bin bool breakpoint bytearray bytes callable chr classmethod compile complex copyright credits delattr dict dir divmod enumerate eval exec exit filter float format frozenset getattr globals hasattr hash help hex id input int isinstance issubclass iter len license list locals map max memoryview min next object oct open ord pow print property quit range repr reversed round set setattr slice sorted staticmethod str sum super tuple type vars zip";
// color text
static SScintillaColors g_rgb_Syntax_python[] =
{ {} };

//--------------------------------
//---- r Language
//--------------------------------
// language
static CString g_str_r_language = _T("r");
// extentions
static CString g_str_r_extention = _T("r");
// comment line
static CString g_str_r_commentline = _T("#");
// comment start
static CString g_str_r_commentStart = _T("");
// comment end
static CString g_str_r_commentEnd = _T("");
// keywords
static const char* g_r_KeyWords =
"if else repeat while function for in next break TRUE FALSE NULL NA Inf NaN"
"abbreviate abline abs acf acos acosh addmargins aggregate agrep alarm alias alist all anova any aov aperm append apply approx approxfun apropos ar args arima array arrows asin asinh assign assocplot atan atanh attach attr attributes autoload autoloader ave axis backsolve barplot basename beta bindtextdomain binomial biplot bitmap bmp body box boxplot bquote break browser builtins bxp by bzfile c call cancor capabilities casefold cat category cbind ccf ceiling character charmatch chartr chol choose chull citation class close cm cmdscale codes coef coefficients col colnames colors colorspaces colours comment complex confint conflicts contour contrasts contributors convolve cophenetic coplot cor cos cosh cov covratio cpgram crossprod cummax cummin cumprod cumsum curve cut cutree cycle data dataentry date dbeta dbinom dcauchy dchisq de debug debugger decompose delay deltat demo dendrapply density deparse deriv det detach determinant deviance dexp df dfbeta dfbetas dffits dgamma dgeom dget dhyper diag diff diffinv difftime digamma dim dimnames dir dirname dist dlnorm dlogis dmultinom dnbinom dnorm dotchart double dpois dput drop dsignrank dt dump dunif duplicated dweibull dwilcox eapply ecdf edit effects eigen emacs embed end environment eval evalq example exists exp expression factanal factor factorial family fft fifo file filter find fitted fivenum fix floor flush for force formals format formula forwardsolve fourfoldplot frame frequency ftable function gamma gaussian gc gcinfo gctorture get getenv geterrmessage gettext gettextf getwd gl glm globalenv gray grep grey grid gsub gzcon gzfile hat hatvalues hcl hclust head heatmap help hist history hsv httpclient iconv iconvlist identical identify if ifelse image influence inherits integer integrate interaction interactive intersect invisible isoreg jitter jpeg julian kappa kernapply kernel kmeans knots kronecker ksmooth labels lag lapply layout lbeta lchoose lcm legend length letters levels lfactorial lgamma library licence license line lines list lm load loadhistory loadings local locator loess log logb logical loglin lowess ls lsfit machine mad mahalanobis makepredictcall manova mapply match matlines matplot matpoints matrix max mean median medpolish menu merge message methods mget min missing mode monthplot months mosaicplot mtext mvfft names napredict naprint naresid nargs nchar ncol next nextn ngettext nlevels nlm nls noquote nrow numeric objects offset open optim optimise optimize options order ordered outer pacf page pairlist pairs palette par parse paste pbeta pbinom pbirthday pcauchy pchisq pdf pentagamma person persp pexp pf pgamma pgeom phyper pi pico pictex pie piechart pipe plclust plnorm plogis plot pmatch pmax pmin pnbinom png pnorm points poisson poly polygon polym polyroot postscript power ppoints ppois ppr prcomp predict preplot pretty princomp print prmatrix prod profile profiler proj promax prompt provide psigamma psignrank pt ptukey punif pweibull pwilcox q qbeta qbinom qbirthday qcauchy qchisq qexp qf qgamma qgeom qhyper qlnorm qlogis qnbinom qnorm qpois qqline qqnorm qqplot qr qsignrank qt qtukey quantile quarters quasi quasibinomial quasipoisson quit qunif quote qweibull qwilcox rainbow range rank raw rbeta rbind rbinom rcauchy rchisq readline real recover rect reformulate regexpr relevel remove reorder rep repeat replace replicate replications require reshape resid residuals restart return rev rexp rf rgamma rgb rgeom rhyper rle rlnorm rlogis rm rmultinom rnbinom rnorm round row rownames rowsum rpois rsignrank rstandard rstudent rt rug runif runmed rweibull rwilcox sample sapply save savehistory scale scan screen screeplot sd search searchpaths seek segments seq sequence serialize setdiff setequal setwd shell sign signif sin single sinh sink smooth solve sort source spectrum spline splinefun split sprintf sqrt stack stars start stderr stdin stdout stem step stepfun stl stop stopifnot str strftime strheight stripchart strptime strsplit strtrim structure strwidth strwrap sub subset substitute substr substring sum summary sunflowerplot supsmu svd sweep switch symbols symnum system t table tabulate tail tan tanh tapply tempdir tempfile termplot terms tetragamma text time title toeplitz tolower topenv toupper trace traceback transform trigamma trunc truncate try ts tsdiag tsp typeof unclass undebug union unique uniroot unix unlink unlist unname unserialize unsplit unstack untrace unz update upgrade url var varimax vcov vector version vi vignette warning warnings weekdays weights which while window windows with write wsbrowser xedit xemacs xfig xinch xor xtabs xyinch yinch zapsmall"
"acme aids aircondit amis aml banking barchart barley beaver bigcity boot brambles breslow bs bwplot calcium cane capability cav censboot channing city claridge cloth cloud coal condense contourplot control corr darwin densityplot dogs dotplot ducks empinf envelope environmental ethanol fir frets gpar grav gravity grob hirose histogram islay knn larrows levelplot llines logit lpoints lsegments lset ltext lvqinit lvqtest manaus melanoma motor multiedit neuro nitrofen nodal ns nuclear oneway parallel paulsen poisons polar qq qqmath remission rfs saddle salinity shingle simplex singer somgrid splom stripplot survival tau tmd tsboot tuna unit urine viewport wireframe wool xyplot"
"acme aids aircondit amis aml banking barchart barley beaver bigcity boot brambles breslow bs bwplot calcium cane capability cav censboot channing city claridge cloth cloud coal condense contourplot control corr darwin densityplot dogs dotplot ducks empinf envelope environmental ethanol fir frets gpar grav gravity grob hirose histogram islay knn larrows levelplot llines logit lpoints lsegments lset ltext lvqinit lvqtest manaus melanoma motor multiedit neuro nitrofen nodal ns nuclear oneway parallel paulsen poisons polar qq qqmath remission rfs saddle salinity shingle simplex singer somgrid splom stripplot survival tau tmd tsboot tuna unit urine viewport wireframe wool xyplot";
// color text
static SScintillaColors g_rgb_Syntax_r[] =
{ {} };

//--------------------------------
//---- rebol Language
//--------------------------------
// language
static CString g_str_rebol_language = _T("rebol");
// extentions
static CString g_str_rebol_extention = _T("rebol");
// comment line
static CString g_str_rebol_commentline = _T(";");
// comment start
static CString g_str_rebol_commentStart = _T("");
// comment end
static CString g_str_rebol_commentEnd = _T("");
// keywords
static const char* g_rebol_KeyWords =
"about abs absolute add alert alias all alter and any any-block? any-function? any-string? any-type? any-word? append arccosine arcsine arctangent array as-pair ask at attempt back binary? bind bitset? block? break brightness? browse build-tag caret-to-offset catch center-face change change-dir char? charset checksum choose clean-path clear clear-fields close comment complement component? compose compress confirm connected? construct context copy cosine datatype? date? debase decimal? decode-cgi decompress dehex delete detab difference dir? dirize disarm dispatch divide do do-events does dump-face dump-obj echo either else email? empty? enbase entab equal? error? even? event? exclude exists? exit exp extract fifth file? find first flash focus for forall foreach forever form forskip found? fourth free func function function? get get-modes get-word? greater-or-equal? greater? halt has hash? head head? help hide hide-popup if image? import-email in in-window? index? info? inform input input? insert integer? intersect issue? join last launch layout length? lesser-or-equal? lesser? library? license link? list-dir list? lit-path? lit-word? load load-image log-10 log-2 log-e logic? loop lowercase make make-dir make-face max maximum maximum-of min minimum minimum-of modified? mold money? multiply native? negate negative? next none? not not-equal? now number? object? odd? offset-to-caret offset? op? open or pair? paren? parse parse-xml path? pick poke port? positive? power prin print probe protect protect-system query quit random read read-io recycle reduce refinement? reform rejoin remainder remold remove remove-each rename repeat repend replace request request-color request-date request-download request-file request-list request-pass request-text resend return reverse routine? same? save script? second secure select send series? set set-modes set-net set-path? set-word? show show-popup sign? sine size-text size? skip sort source span? split-path square-root strict-equal? strict-not-equal? string? struct? stylize subtract suffix? switch tag? tail tail? tangent third throw time? to to-binary to-bitset to-block to-char to-date to-decimal to-email to-file to-get-word to-hash to-hex to-idate to-image to-integer to-issue to-list to-lit-path to-lit-word to-local-file to-logic to-money to-pair to-paren to-path to-rebol-file to-refinement to-set-path to-set-word to-string to-tag to-time to-tuple to-url to-word trace trim try tuple? type? unfocus union unique unprotect unset unset? until unview update upgrade uppercase url? usage use value? view viewed? wait what what-dir while within? word? write write-io xor zero?"
"action? any-block? any-function? any-string? any-type? any-word? binary? bitset? block? char? component? connected? datatype? date? decimal? dir? email? empty? equal? error? even? event? exists? file? found? function? get-word? greater-or-equal greater? hash? head? image? index? info? input? integer? issue? length? lesser-or-equal? lesser? library? link-app? link? list? lit-path? lit-word? logic? modified? money? native? negative? none? not-equal? number? object? odd? offset? op? pair? paren? path? port? positive? rebol-command? rebol-encap? rebol-link? rebol-pro? rebol-view? refinement? routine? same? script? series? set-path? set-word? sign? size? strict-equal? strict-not-equal string? struct? suffix? tag? tail? time? tuple? type? unset? url? value? view? word? zero?"
"action! any-block! any-function! any-string! any-type!  any-word! binary! bitset! block! char! datatype! date! decimal! email! error!  event! file! function! get-word! hash! image! integer! issue! library! list! lit-path!  lit-word! logic! money! native! none! number! object! op! pair! paren! path!  port! refinement! routine! series! set-path! set-word! string! struct! symbol! tag!  time! tuple! unset! url! word!"
""
""
""
""
"";
// color text
static SScintillaColors g_rgb_Syntax_rebol[] =
{ {} };

//--------------------------------
//---- registry Language
//--------------------------------
// language
static CString g_str_registry_language = _T("registry");
// extentions
static CString g_str_registry_extention = _T("registry");
// comment line
static CString g_str_registry_commentline = _T(";;");
// comment start
static CString g_str_registry_commentStart = _T("");
// comment end
static CString g_str_registry_commentEnd = _T("");
// keywords
static const char* g_registry_KeyWords =
// color text
static SScintillaColors g_rgb_Syntax_registry[] =
{ {} };

//--------------------------------
//---- rc Language
//--------------------------------
// language
static CString g_str_rc_language = _T("rc");
// extentions
static CString g_str_rc_extention = _T("rc");
// comment line
static CString g_str_rc_commentline = _T("//");
// comment start
static CString g_str_rc_commentStart = _T("/*");
// comment end
static CString g_str_rc_commentEnd = _T("*/");
// keywords
static const char* g_rc_KeyWords =
"ACCELERATORS ALT AUTO3STATE AUTOCHECKBOX AUTORADIOBUTTON BEGIN BITMAP BLOCK BUTTON CAPTION CHARACTERISTICS CHECKBOX CLASS COMBOBOX CONTROL CTEXT CURSOR DEFPUSHBUTTON DIALOG DIALOGEX DISCARDABLE EDITTEXT END EXSTYLE FONT GROUPBOX ICON LANGUAGE LISTBOX LTEXT MENU MENUEX MENUITEM MESSAGETABLE POPUP PUSHBUTTON RADIOBUTTON RCDATA RTEXT SCROLLBAR SEPARATOR SHIFT STATE3 STRINGTABLE STYLE TEXTINCLUDE VALUE VERSION VERSIONINFO VIRTKEY"
"ACCELERATORS ALT AUTO3STATE AUTOCHECKBOX AUTORADIOBUTTON BEGIN BITMAP BLOCK BUTTON CAPTION CHARACTERISTICS CHECKBOX CLASS COMBOBOX CONTROL CTEXT CURSOR DEFPUSHBUTTON DIALOG DIALOGEX DISCARDABLE EDITTEXT END EXSTYLE FONT GROUPBOX ICON LANGUAGE LISTBOX LTEXT MENU MENUEX MENUITEM MESSAGETABLE POPUP PUSHBUTTON RADIOBUTTON RCDATA RTEXT SCROLLBAR SEPARATOR SHIFT STATE3 STRINGTABLE STYLE TEXTINCLUDE VALUE VERSION VERSIONINFO VIRTKEY";
// color text
static SScintillaColors g_rgb_Syntax_rc[] =
{ {} };

//--------------------------------
//---- ruby Language
//--------------------------------
// language
static CString g_str_ruby_language = _T("ruby");
// extentions
static CString g_str_ruby_extention = _T("ruby");
// comment line
static CString g_str_ruby_commentline = _T("#");
// comment start
static CString g_str_ruby_commentStart = _T("");
// comment end
static CString g_str_ruby_commentEnd = _T("");
// keywords
static const char* g_ruby_KeyWords =
"ARGF ARGV BEGIN END ENV FALSE DATA NIL RUBY_PATCHLEVEL RUBY_PLATFORM RUBY_RELEASE_DATE RUBY_VERSION PLATFORM RELEASE_DATE STDERR STDIN STDOUT TOPLEVEL_BINDING TRUE __ENCODING__ __END__ __FILE__ __LINE__ alias and begin break case class def defined? do else elsif end ensure false for if in module next nil not or redo rescue retry return self super then true undef unless until when while yield"
"ARGF ARGV BEGIN END ENV FALSE DATA NIL RUBY_PATCHLEVEL RUBY_PLATFORM RUBY_RELEASE_DATE RUBY_VERSION PLATFORM RELEASE_DATE STDERR STDIN STDOUT TOPLEVEL_BINDING TRUE __ENCODING__ __END__ __FILE__ __LINE__ alias and begin break case class def defined? do else elsif end ensure false for if in module next nil not or redo rescue retry return self super then true undef unless until when while yield";
// color text
static SScintillaColors g_rgb_Syntax_ruby[] =
{ {} };

//--------------------------------
//---- rust Language
//--------------------------------
// language
static CString g_str_rust_language = _T("rust");
// extentions
static CString g_str_rust_extention = _T("rust");
// comment line
static CString g_str_rust_commentline = _T("//");
// comment start
static CString g_str_rust_commentStart = _T("/*");
// comment end
static CString g_str_rust_commentEnd = _T("*/");
// keywords
static const char* g_rust_KeyWords =
"abstract as async become box break const continue crate do dyn else enum extern false final fn for if impl in let loop macro match mod move mut override priv pub ref return self static struct super trait true try type typeof unsafe unsized use virtual where while yield"
"bool char f32 f64 i128 i16 i32 i64 i8 isize str u128 u16 u32 u64 u8 usize"
"Self"
""
""
""
""
"";
// color text
static SScintillaColors g_rgb_Syntax_rust[] =
{ {} };

//--------------------------------
//---- scheme Language
//--------------------------------
// language
static CString g_str_scheme_language = _T("scheme");
// extentions
static CString g_str_scheme_extention = _T("scheme");
// comment line
static CString g_str_scheme_commentline = _T(";");
// comment start
static CString g_str_scheme_commentStart = _T("");
// comment end
static CString g_str_scheme_commentEnd = _T("");
// keywords
static const char* g_scheme_KeyWords =
"+ - * / = < > <= >= => abs acos and angle append apply asin assoc assq assv atan begin boolean? caar cadr call-with-current-continuation call/cc call-with-input-file call-with-output-file call-with-values car cdr cdar cddr caaar caadr cadar caddr cdaar cdadr cddar cdddr caaaar caaadr caadar caaddr cadaar cadadr caddar cadddr cdaaar cdaadr cdadar cdaddr cddaar cddadr cdddar cddddr case ceiling char->integer char-alphabetic? char-ci<=? char-ci<? char-ci=? char-ci>=? char-ci>? char-downcase char-lower-case? char-numeric? char-ready? char-upcase char-upper-case? char-whitespace? char<=? char<? char=? char>=? char>? char? close-input-port close-output-port complex? cond cons cos current-input-port current-output-port define define-syntax delay denominator display do dynamic-wind else eof-object? eq? equal? eqv? eval even? exact->inexact exact? exp expt floor for-each force gcd if imag-part inexact->exact inexact? input-port? integer->char integer? interaction-environment lambda lcm length let let* let-syntax letrec letrec-syntax list list->string list->vector list-ref list-tail list? load log magnitude make-polar make-rectangular make-string make-vector map max member memq memv min modulo negative? newline not null-environment null? number->string number? numerator odd? open-input-file open-output-file or output-port? pair? peek-char positive? procedure? quasiquote quote quotient rational? rationalize read read-char real-part real? remainder reverse round scheme-report-environment set! set-car! set-cdr! sin sqrt string string->list string->number string->symbol string-append string-ci<=? string-ci<? string-ci=? string-ci>=? string-ci>? string-copy string-fill! string-length string-ref string-set! string<=? string<? string=? string>=? string>? string? substring symbol->string symbol? syntax-rules transcript-off transcript-on truncate unquote unquote-splicing values vector vector->list vector-fill! vector-length vector-ref vector-set! vector? with-input-from-file with-output-to-file write write-char zero?"
""
"";
// color text
static SScintillaColors g_rgb_Syntax_scheme[] =
{ {} };

//--------------------------------
//---- smalltalk Language
//--------------------------------
// language
static CString g_str_smalltalk_language = _T("smalltalk");
// extentions
static CString g_str_smalltalk_extention = _T("smalltalk");
// comment line
static CString g_str_smalltalk_commentline = _T("");
// comment start
static CString g_str_smalltalk_commentStart = _T(""");
// comment end
static CString g_str_smalltalk_commentEnd = _T(""");
// keywords
static const char* g_smalltalk_KeyWords =
"ifTrue: ifFalse: whileTrue: whileFalse: ifNil: ifNotNil: whileTrue whileFalse repeat isNil notNil"
"ifTrue: ifFalse: whileTrue: whileFalse: ifNil: ifNotNil: whileTrue whileFalse repeat isNil notNil";
// color text
static SScintillaColors g_rgb_Syntax_smalltalk[] =
{ {} };

//--------------------------------
//---- spice Language
//--------------------------------
// language
static CString g_str_spice_language = _T("spice");
// extentions
static CString g_str_spice_extention = _T("spice");
// comment line
static CString g_str_spice_commentline = _T("*");
// comment start
static CString g_str_spice_commentStart = _T("");
// comment end
static CString g_str_spice_commentEnd = _T("");
// keywords
static const char* g_spice_KeyWords =
"ac alias alter alterparam append askvalues assertvalid autoscale break compose copy copytodoc dc delete destroy destroyvec diff display disto dowhile echo else end errorstop fftinit filter foreach fourier freqtotime function functionundef goto homecursors if isdisplayed label let linearize listing load loadaccumulator makelabel movelabel makesmithplot movecursorleft movecursorright msgbox nameplot newplot nextparam noise nopoints op plot plotf plotref poly print printcursors printevent printname printplot printstatus printtext printtol printunits printval printvector pwl pz quit removesmithplot rename repeat resume rotate runs rusage save sendplot sendscript sens set setcursor setdoc setlabel setlabeltype setmargins setnthtrigger setunits setvec setparam setplot setquery setscaletype settracecolor settracestyle setsource settrigger setvec setxlimits setylimits show showmod sort status step stop switch tf timetofreq timetowave tran unalias unlet unset unalterparam update version view wavefilter wavetotime where while write"
"abs askvalue atan average ceil cos db differentiate differentiatex exp finalvalue floor getcursorx getcursory getcursory0 getcursory1 getparam im ln initialvalue integrate integratex interpolate isdef isdisplayed j log length mag, max maxscale mean meanpts min minscale nextplot nextvector norm operatingpoint ph phase phaseextend pk_pk pos pulse re rms rmspts rnd sameplot sin sqrt stddev stddevpts tan tfall tolerance trise unitvec vector"
"param nodeset include options dcconv subckt ends model"
"param nodeset include options dcconv subckt ends model";
// color text
static SScintillaColors g_rgb_Syntax_spice[] =
{ {} };

//--------------------------------
//---- sql Language
//--------------------------------
// language
static CString g_str_sql_language = _T("sql");
// extentions
static CString g_str_sql_extention = _T("sql");
// comment line
static CString g_str_sql_commentline = _T("--");
// comment start
static CString g_str_sql_commentStart = _T("/*");
// comment end
static CString g_str_sql_commentEnd = _T("*/");
// keywords
static const char* g_sql_KeyWords =
"abs absolute access acos add add_months adddate admin after aggregate all allocate alter and any app_name applock_mode applock_test are array as asc ascii asin assemblyproperty assertion asymkey_id at atan atn2 audit authid authorization autonomous_transaction avg backup before begin benchmark between bfilename bin binary_checksum bit_and bit_count bit_or body both breadth break browse bulk by call cascade cascaded case cast catalog catch ceil ceiling cert_id certproperty character charindex chartorowid check checkpoint checksum checksum_agg chr class clause close cluster clustered coalesce col_length col_name collate collation collect column columnproperty columns_updated comment commit completion compress compute concat concat_ws connect connection connectionproperty constant constraint constraints constructorcreate contains containsable containstable context_info continue conv convert corr corresponding cos cot count count_big covar_pop covar_samp create cross cube cume_dist current current_date current_path current_request_id current_role current_time current_timestamp current_user currval cursor_status cycle data database database_principal_id databasepropertyex datalength date_add date_format date_sub dateadd datediff datefirst dateformat datename datepart db_id db_name dbcc deallocate declare decode decryptbyasmkey decryptbycert decryptbykey decryptbykeyautocert decryptbypassphrase default deferrable deferred degrees delete dense_rank deny depth deref desc describe descriptor destroy destructor deterministic diagnostics dictionary difference disconnect disk distinct distributed do domain drop dump dynamic each else elsif empth encode encrypt encryptbyasmkey encryptbycert encryptbykey encryptbypassphrase end end-exec equals errlvl error_line error_message error_number error_procedure error_severity error_state escape eventdata every except exception exclusive exec execute exists exit exp export_set extends external extract false fetch file file_id file_idex file_name filegroup_id filegroup_name filegroupproperty fileproperty fillfactor first first_value floor fn_virtualfilestats for forall foreign format formatmessage found freetext freetexttable from from_days full fulltextcatalog fulltextcatalogproperty fulltextservice fulltextserviceproperty function general get get_filestream_transaction_context get_lock getansinull getdate getutcdate global go goto grant greatest group grouping grouping_id has_perms_by_name hashbytes having heap hex hextoraw holdlock host host_id host_name hour ident_current ident_incr ident_seed identified identity identity_insert identitycol if ifnull ignore immediate in include increment index index_col indexkey_property indexproperty indicator initcap initial initialize initially inner inout input insert instr instrb interface intersect into is is_member is_null is_numeric is_srvrolemember isdate isnull isnumeric isolation iterate java join key key_guid key_id kill lag language large last last_day last_value lateral lcase lead leading least left len length lengthb less level like limit limited lineno ln load local localtime localtimestamp locator lock log log10 loop lower lpad ltrim make_ref map match max maxextents merge mid min min_active_rowversion minus minute mlslabel mod mode modifies modify module month months_between names national natural naturaln new new_time newid newsequentialid next next_day nextval no noaudit nocheck nocompress nocopy nonclustered none not nowait ntile null nullif number_base nvl nvl2 object object_definition object_id object_name object_property object_schema_name objectproperty objectpropertyex ocirowid oct of off offline offsets old on online only opaque open opendatasource openquery openrowset openxml operation operator option or ord order ordinalityorganization original_db_name original_login others out outer output over package pad parameter parameters parsename partial partition path pathname patindex pctfree percent percent_rank permissions pi pivot plan pls_integer positive positiven postfix pow power pragma prefix preorder prepare preserve primary print prior private privileges proc procedure public publishingservername pwdcompare pwdencrypt quotename radians raise raiserror rand range rank ratio_to_export rawtohex read reads readtext reconfigure record recursive ref references referencing reftohex relative release release_lock rename repeat replace replicate replication resource restore restrict result return returns reverse revert revoke right rollback rollup round routine row row_number rowcount rowcount_big rowguidcol rowidtochar rowlabel rownum rows rowtype rpad rtrim rule save savepoint schema schema_id schema_name scope scope_identity scroll search second section securityaudit seddev_samp select separate sequence serverproperty session session_user set sets setuser share shutdown sign signbyasymkey signbycert sin sinh size some soundex sp_helplanguage space specific specifictype sql sql_variant_property sqlcode sqlerrm sqlexception sqlstate sqlwarning sqrt square start state statement static statistics stats_date std stddev stdev stdev_pop stdevp str strcmp structure stuff subdate substr substrb substring substring_index subtype successful sum suser_id suser_name suser_sid suser_sname switchoffset synonym sys_context sys_guid sysdate sysdatetime sysdatetimeoffset system_user sysutcdatetime table tablesample tan tanh temporary terminate textptr textsize textvalid than then timezone_abbr timezone_hour timezone_minute timezone_region to to_char to_date to_days to_number to_single_byte todatetimeoffset top trailing tran transaction translate translation treat trigger trigger_nestlevel trim true trunc truncate try tsequal type type_id type_name typeproperty ucase uid under unicode union unique unknown unnest unpivot update updatetext upper usage use user user_id user_name userenv using validate value values var var_pop var_samp variable variance varp varying verifysignedbyasmkey verifysignedbycert view vsize waitfor when whenever where while with without work write writetext xact_state zone"
""
"bfile bigint binary binary_integer bit blob bool boolean char char_base clob cursor date datetime datetime2 datetimeoffset day dec decimal double enum float hierarchyid image int integer interval long longblob longtext mediumblob mediumint mediumtext money nchar nclob ntext number numeric nvarchar precision raw real rowid smalldatetime smallint smallmoney sql_variant text time timestamp tinyblob tinyint tinytext uniqueidentifier urowid varbinary varchar varchar2 xml year"
"bfile bigint binary binary_integer bit blob bool boolean char char_base clob cursor date datetime datetime2 datetimeoffset day dec decimal double enum float hierarchyid image int integer interval long longblob longtext mediumblob mediumint mediumtext money nchar nclob ntext number numeric nvarchar precision raw real rowid smalldatetime smallint smallmoney sql_variant text time timestamp tinyblob tinyint tinytext uniqueidentifier urowid varbinary varchar varchar2 xml year";
// color text
static SScintillaColors g_rgb_Syntax_sql[] =
{ {} };

//--------------------------------
//---- srec Language
//--------------------------------
// language
static CString g_str_srec_language = _T("srec");
// extentions
static CString g_str_srec_extention = _T("srec");
// comment line
static CString g_str_srec_commentline = _T("");
// comment start
static CString g_str_srec_commentStart = _T("");
// comment end
static CString g_str_srec_commentEnd = _T("");
// keywords
static const char* g_srec_KeyWords =
// color text
static SScintillaColors g_rgb_Syntax_srec[] =
{ {} };

//--------------------------------
//---- swift Language
//--------------------------------
// language
static CString g_str_swift_language = _T("swift");
// extentions
static CString g_str_swift_extention = _T("swift");
// comment line
static CString g_str_swift_commentline = _T("//");
// comment start
static CString g_str_swift_commentStart = _T("/*");
// comment end
static CString g_str_swift_commentEnd = _T("*/");
// keywords
static const char* g_swift_KeyWords =
"class deinit enum extension func import init internal let operator private protocol public static struct subscript typealias var keywordclass.swift.statements=break case continue default do else fallthrough for if in return switch where while"
"as dynamicType false is nil self Self super true __COLUMN__ __FILE__ __FUNCTION__ __LINE__"
"associativity convenience dynamic didSet final get infix inout lazy left mutating none nonmutating optional override postfix precedence prefix Protocol required right set Type unowned weak willSet"
"associativity convenience dynamic didSet final get infix inout lazy left mutating none nonmutating optional override postfix precedence prefix Protocol required right set Type unowned weak willSet";
// color text
static SScintillaColors g_rgb_Syntax_swift[] =
{ {} };

//--------------------------------
//---- tcl Language
//--------------------------------
// language
static CString g_str_tcl_language = _T("tcl");
// extentions
static CString g_str_tcl_extention = _T("tcl");
// comment line
static CString g_str_tcl_commentline = _T("#");
// comment start
static CString g_str_tcl_commentStart = _T("");
// comment end
static CString g_str_tcl_commentEnd = _T("");
// keywords
static const char* g_tcl_KeyWords =
"after append apply array auto_execok auto_import auto_load auto_load_index auto_qualify auto_reset bgerror binary break catch cd chan clock close concat continue coroutine dde dict default else elseif encoding env eof error eval exec exit expr fblocked fconfigure fcopy file fileevent filename flush for foreach format gets glob global history http if incr info interp join lappend lassign lindex linsert list llength lmap load lrange lrepeat lreplace lreverse lsearch lset lsort memory my namespace next nextto oo::class oo::copy oo::define oo::objdefine oo::object open package parray pid pkg_mkIndex platform proc puts pwd read regexp registry regsub rename return scan seek self set socket source split string subst switch tailcall tclLog tclMacPkgSearch tclPkgSetup tclPkgUnknown tell throw time trace try unknown unload unset update uplevel upvar variable vwait while yield yeildto zlib"
"bell bind bindtags button canvas checkbutton console destroy entry event focus font frame grab grid image label labelframe listbox lower menu menubutton message option pack panedwindow place radiobutton raise scale scrollbar selection send spinbox text tk tkerror tkwait toplevel ttk::button ttk::checkbutton ttk::combobox ttk::entry ttk::frame ttk::intro ttk::label ttk::labeframe ttk::menubutton ttk::notebook ttk::panedwindow ttk::progressbar ttk::radiobutton ttk::scale ttk::scrollbar ttk::sizegrip ttk::spinbox ttk::style winfo wm"
"@scope body class code common component configbody constructor define destructor hull import inherit itcl itk itk_component itk_initialize itk_interior itk_option iwidgets keep method private protected public"
"tkButtonDown tkButtonEnter tkButtonInvoke tkButtonLeave tkButtonUp tkCancelRepeat tkCheckRadioInvoke tkDarken tkEntryAutoScan tkEntryBackspace tkEntryButton1 tkEntryClosestGap tkEntryInsert tkEntryKeySelect tkEntryMouseSelect tkEntryNextWord tkEntryPaste tkEntryPreviousWord tkEntrySeeInsert tkEntrySetCursor tkEntryTranspose tkEventMotifBindings tkFDGetFileTypes tkFirstMenu tkFocusGroup_Destroy tkFocusGroup_In tkFocusGroup_Out tkFocusOK tkListboxAutoScan tkListboxBeginExtend tkListboxBeginSelect tkListboxBeginToggle tkListboxCancel tkListboxDataExtend tkListboxExtendUpDown tkListboxMotion tkListboxSelectAll tkListboxUpDown tkMbButtonUp tkMbEnter tkMbLeave tkMbMotion tkMbPost tkMenuButtonDown tkMenuDownArrow tkMenuDup tkMenuEscape tkMenuFind tkMenuFindName tkMenuFirstEntry tkMenuInvoke tkMenuLeave tkMenuLeftArrow tkMenuMotion tkMenuNextEntry tkMenuNextMenu tkMenuRightArrow tkMenuUnpost tkMenuUpArrow tkMessageBox tkPostOverPoint tkRecolorTree tkRestoreOldGrab tkSaveGrabInfo tkScaleActivate tkScaleButton2Down tkScaleButtonDown tkScaleControlPress tkScaleDrag tkScaleEndDrag tkScaleIncrement tkScreenChanged tkScrollButton2Down tkScrollButtonDown tkScrollButtonUp tkScrollByPages tkScrollByUnits tkScrollDrag tkScrollEndDrag tkScrollSelect tkScrollStartDrag tkScrollToPos  tkScrollTopBottom tkTabToWindow tkTearOffMenu tkTextAutoScan tkTextButton1 tkTextClosestGap tkTextInsert tkTextKeyExtend tkTextKeySelect tkTextNextPara tkTextNextPos tkTextNextWord tkTextPaste tkTextPrevPara tkTextPrevPos tkTextResetAnchor tkTextScrollPages tkTextSelectTo tkTextSetCursor tkTextTranspose tkTextUpDownLine tkTraverseToMenu tkTraverseWithinMenu tk_bisque tk_chooseColor tk_dialog tk_focusFollowsMouse tk_focusNext tk_focusPrev tk_getOpenFile tk_getSaveFile tk_messageBox tk_optionMenu tk_popup tk_setPalette tk_textCopy tk_textCut tk_textPaste"
"tkButtonDown tkButtonEnter tkButtonInvoke tkButtonLeave tkButtonUp tkCancelRepeat tkCheckRadioInvoke tkDarken tkEntryAutoScan tkEntryBackspace tkEntryButton1 tkEntryClosestGap tkEntryInsert tkEntryKeySelect tkEntryMouseSelect tkEntryNextWord tkEntryPaste tkEntryPreviousWord tkEntrySeeInsert tkEntrySetCursor tkEntryTranspose tkEventMotifBindings tkFDGetFileTypes tkFirstMenu tkFocusGroup_Destroy tkFocusGroup_In tkFocusGroup_Out tkFocusOK tkListboxAutoScan tkListboxBeginExtend tkListboxBeginSelect tkListboxBeginToggle tkListboxCancel tkListboxDataExtend tkListboxExtendUpDown tkListboxMotion tkListboxSelectAll tkListboxUpDown tkMbButtonUp tkMbEnter tkMbLeave tkMbMotion tkMbPost tkMenuButtonDown tkMenuDownArrow tkMenuDup tkMenuEscape tkMenuFind tkMenuFindName tkMenuFirstEntry tkMenuInvoke tkMenuLeave tkMenuLeftArrow tkMenuMotion tkMenuNextEntry tkMenuNextMenu tkMenuRightArrow tkMenuUnpost tkMenuUpArrow tkMessageBox tkPostOverPoint tkRecolorTree tkRestoreOldGrab tkSaveGrabInfo tkScaleActivate tkScaleButton2Down tkScaleButtonDown tkScaleControlPress tkScaleDrag tkScaleEndDrag tkScaleIncrement tkScreenChanged tkScrollButton2Down tkScrollButtonDown tkScrollButtonUp tkScrollByPages tkScrollByUnits tkScrollDrag tkScrollEndDrag tkScrollSelect tkScrollStartDrag tkScrollToPos  tkScrollTopBottom tkTabToWindow tkTearOffMenu tkTextAutoScan tkTextButton1 tkTextClosestGap tkTextInsert tkTextKeyExtend tkTextKeySelect tkTextNextPara tkTextNextPos tkTextNextWord tkTextPaste tkTextPrevPara tkTextPrevPos tkTextResetAnchor tkTextScrollPages tkTextSelectTo tkTextSetCursor tkTextTranspose tkTextUpDownLine tkTraverseToMenu tkTraverseWithinMenu tk_bisque tk_chooseColor tk_dialog tk_focusFollowsMouse tk_focusNext tk_focusPrev tk_getOpenFile tk_getSaveFile tk_messageBox tk_optionMenu tk_popup tk_setPalette tk_textCopy tk_textCut tk_textPaste";
// color text
static SScintillaColors g_rgb_Syntax_tcl[] =
{ {} };

//--------------------------------
//---- tehex Language
//--------------------------------
// language
static CString g_str_tehex_language = _T("tehex");
// extentions
static CString g_str_tehex_extention = _T("tehex");
// comment line
static CString g_str_tehex_commentline = _T("");
// comment start
static CString g_str_tehex_commentStart = _T("");
// comment end
static CString g_str_tehex_commentEnd = _T("");
// keywords
static const char* g_tehex_KeyWords =
// color text
static SScintillaColors g_rgb_Syntax_tehex[] =
{ {} };

//--------------------------------
//---- tex Language
//--------------------------------
// language
static CString g_str_tex_language = _T("tex");
// extentions
static CString g_str_tex_extention = _T("tex");
// comment line
static CString g_str_tex_commentline = _T("%");
// comment start
static CString g_str_tex_commentStart = _T("");
// comment end
static CString g_str_tex_commentEnd = _T("");
// keywords
static const char* g_tex_KeyWords =
// color text
static SScintillaColors g_rgb_Syntax_tex[] =
{ {} };

//--------------------------------
//---- vb Language
//--------------------------------
// language
static CString g_str_vb_language = _T("vb");
// extentions
static CString g_str_vb_extention = _T("vb");
// comment line
static CString g_str_vb_commentline = _T("'");
// comment start
static CString g_str_vb_commentStart = _T("");
// comment end
static CString g_str_vb_commentEnd = _T("");
// keywords
static const char* g_vb_KeyWords =
"addhandler addressof alias and andalso as boolean by byref byte byval call case catch cbool cbyte cchar cdate cdbl cdec char cint class clng cobj const continue csbyte cshort csng cstr ctype cuint culng cushort date decimal declare default delegate dim directcast do double each else elseif end endif enum erase error event exit false finally for friend function get gettype global gosub goto handles if implements imports in inherits integer interface is isnot let lib like long loop me mod module mustinherit mustoverride mybase myclass namespace narrowing new next not nothing notinheritable notoverridable object of on operator option optional or orelse out overloads overridable overrides paramarray partial private property protected public raiseevent readonly redim rem removehandler resume return sbyte select set shadows shared short single static step stop strict string structure sub synclock then throw to true try trycast typeof uinteger ulong ushort using variant wend when while widening with withevents writeonly xor attribute begin currency implement load lset rset type unload aggregate ansi assembly async auto await binary compare custom distinct equals explicit from group into isfalse istrue iterator join key mid off order preserve skip take text unicode until where yield"
"addhandler addressof alias and andalso as boolean by byref byte byval call case catch cbool cbyte cchar cdate cdbl cdec char cint class clng cobj const continue csbyte cshort csng cstr ctype cuint culng cushort date decimal declare default delegate dim directcast do double each else elseif end endif enum erase error event exit false finally for friend function get gettype global gosub goto handles if implements imports in inherits integer interface is isnot let lib like long loop me mod module mustinherit mustoverride mybase myclass namespace narrowing new next not nothing notinheritable notoverridable object of on operator option optional or orelse out overloads overridable overrides paramarray partial private property protected public raiseevent readonly redim rem removehandler resume return sbyte select set shadows shared short single static step stop strict string structure sub synclock then throw to true try trycast typeof uinteger ulong ushort using variant wend when while widening with withevents writeonly xor attribute begin currency implement load lset rset type unload aggregate ansi assembly async auto await binary compare custom distinct equals explicit from group into isfalse istrue iterator join key mid off order preserve skip take text unicode until where yield";
// color text
static SScintillaColors g_rgb_Syntax_vb[] =
{ {} };

//--------------------------------
//---- txt2tags Language
//--------------------------------
// language
static CString g_str_txt2tags_language = _T("txt2tags");
// extentions
static CString g_str_txt2tags_extention = _T("txt2tags");
// comment line
static CString g_str_txt2tags_commentline = _T("");
// comment start
static CString g_str_txt2tags_commentStart = _T("");
// comment end
static CString g_str_txt2tags_commentEnd = _T("");
// keywords
static const char* g_txt2tags_KeyWords =
// color text
static SScintillaColors g_rgb_Syntax_txt2tags[] =
{ {} };

//--------------------------------
//---- verilog Language
//--------------------------------
// language
static CString g_str_verilog_language = _T("verilog");
// extentions
static CString g_str_verilog_extention = _T("verilog");
// comment line
static CString g_str_verilog_commentline = _T("//");
// comment start
static CString g_str_verilog_commentStart = _T("/*");
// comment end
static CString g_str_verilog_commentEnd = _T("*/");
// keywords
static const char* g_verilog_KeyWords =
"accept_on alias always always_comb always_ff always_latch and assert assign assume attribute automatic before begin bind bins binsof bit break buf bufif0 bufif1 byte case casex casez cell chandle checker class clocking cmos config const constraint context continue cover covergroup coverpoint cross deassign default defparam design disable dist do edge else end endattribute endcase endchecker endclass endclocking endconfig endfunction endgenerate endgroup endinterface endmodule endpackage endprimitive endprogram endproperty endsequence endspecify endtable endtask enum event eventually expect export extends extern final first_match for force foreach forever fork forkjoin function generate genvar global highz0 highz1 if iff ifnone ignore_bins illegal_bins implements implies import incdir include initial inout input inside instance int integer interconnect interface intersect join join_any join_none large let liblist library local localparam logic longint macromodule matches medium modport module nand negedge nettype new nexttime nmos nor noshowcancelled not notif0 notif1 null or output package packed parameter pmos posedge primitive priority program property protected pull0 pull1 pulldown pullup pulsestyle_ondetect pulsestyle_onevent pure rand randc randcase randsequence rcmos real realtime ref reg reject_on release repeat restrict return rnmos rpmos rtran rtranif0 rtranif1 scalared sequence shortint shortreal showcancelled signed small soft solve specify specparam static string strong strong0 strong1 struct super supply0 supply1 sync_accept_on sync_reject_on s_always s_eventually s_nexttime s_until s_until_with table tagged task this throughout time timeprecision timeunit tran tranif0 tranif1 tri tri0 tri1 triand trior trireg type typedef union unique unique0 unsigned until until_with untyped use var vectored virtual void wait wait_order wand weak weak0 weak1 while wildcard wire with within wor xnor xor"
"$acos $acosh $asin $asinh $assertcontrol $assertkill $assertoff $asserton $assertpasson $assertpassoff $assertfailon $assertfailoff $assertnonvacuouson $assertvacuousoff $async$and$array $async$and$plane $async$nand$array $async$nand$plane $async$nor$array $async$nor$plane $async$or$array $async$or$plane $atan $atan2 $atanh $bits $bitstoreal $bitstoshortreal $cast $ceil $changed_gclk $changing_gclk $clog2 $comment $cos $cosh $countdrivers $countones $coverage_control $coverage_get $coverage_get_max $coverage_merge $coverage_save $date $dimensions $display $displayb $displayh $displayo $dist_chi_square $dist_erlang $dist_exponential $dist_normal $dist_poisson $dist_t $dist_uniform $dumpall $dumpfile $dumpflush $dumplimit $dumpoff $dumpon $dumpportsall $dumpportsflush $dumpportslimit $dumpportsoff $dumpportson $dumpvars $end $enddefinitions $error $exit $exp $falling_gclk $fatal $fclose $fdisplay $fdisplayb $fdisplayh $fdisplayo $fell $fell_gclk $feof $ferror $fflush $fgetc $fgets $finish $floor $fmonitor $fmonitorb $fmonitorh $fmonitoro $fopen $fread $fscanf $fseek $fstrobe $ftell $fullskew $future_gclk $fwrite $fwriteb $fwriteh $fwriteo $getpattern $get_coverage $high $history $hold $hypot $increment $incsave $info $input $isunbounded $isunknown $itor $key $left $list $ln $load_coverage_db $log $log10 $low $monitor $monitorb $monitorh $monitoro $monitoroff $monitoron $nochange $nokey $nolog $onehot $onehot0 $past $past_gclk $period $pow $printtimescale $q_add $q_exam $q_full $q_initialize $q_remove $random $readmemb $readmemh $realtime $realtobits $recovery $recrem $removal $reset $reset_count $reset_value $restart $rewind $right $rising_gclk $root $rose $rose_gclk $rtoi $sampled $save $scale $scope $setup $setuphold $set_coverage_db_name $sformat $sformatf $shortrealtobits $showscopes $showvariables $showvars $signed $sin $sinh $size $skew $sqrt $sreadmemb $sreadmemh $sscanf $stable $stable_gclk $steady_gclk $stime $stop $strobe $strobeb $strobeh $strobeo $swrite $sync$and$array $sync$and$plane $sync$nand$array $sync$nand$plane $sync$nor$array $sync$nor$plane $sync$or$array $sync$or$plane $system $tan $tanh $test$plusargs $time $timeformat $timescale $timeskew $typename $typeof $uandom $ungetc $unit $unpacked_dimensions $unsigned $upscope $urandom_range $value$plusargs $var $vcdclose $version $warning $width $write $writeb $writeh $writememb $writememh $writeo"
"$acos $acosh $asin $asinh $assertcontrol $assertkill $assertoff $asserton $assertpasson $assertpassoff $assertfailon $assertfailoff $assertnonvacuouson $assertvacuousoff $async$and$array $async$and$plane $async$nand$array $async$nand$plane $async$nor$array $async$nor$plane $async$or$array $async$or$plane $atan $atan2 $atanh $bits $bitstoreal $bitstoshortreal $cast $ceil $changed_gclk $changing_gclk $clog2 $comment $cos $cosh $countdrivers $countones $coverage_control $coverage_get $coverage_get_max $coverage_merge $coverage_save $date $dimensions $display $displayb $displayh $displayo $dist_chi_square $dist_erlang $dist_exponential $dist_normal $dist_poisson $dist_t $dist_uniform $dumpall $dumpfile $dumpflush $dumplimit $dumpoff $dumpon $dumpportsall $dumpportsflush $dumpportslimit $dumpportsoff $dumpportson $dumpvars $end $enddefinitions $error $exit $exp $falling_gclk $fatal $fclose $fdisplay $fdisplayb $fdisplayh $fdisplayo $fell $fell_gclk $feof $ferror $fflush $fgetc $fgets $finish $floor $fmonitor $fmonitorb $fmonitorh $fmonitoro $fopen $fread $fscanf $fseek $fstrobe $ftell $fullskew $future_gclk $fwrite $fwriteb $fwriteh $fwriteo $getpattern $get_coverage $high $history $hold $hypot $increment $incsave $info $input $isunbounded $isunknown $itor $key $left $list $ln $load_coverage_db $log $log10 $low $monitor $monitorb $monitorh $monitoro $monitoroff $monitoron $nochange $nokey $nolog $onehot $onehot0 $past $past_gclk $period $pow $printtimescale $q_add $q_exam $q_full $q_initialize $q_remove $random $readmemb $readmemh $realtime $realtobits $recovery $recrem $removal $reset $reset_count $reset_value $restart $rewind $right $rising_gclk $root $rose $rose_gclk $rtoi $sampled $save $scale $scope $setup $setuphold $set_coverage_db_name $sformat $sformatf $shortrealtobits $showscopes $showvariables $showvars $signed $sin $sinh $size $skew $sqrt $sreadmemb $sreadmemh $sscanf $stable $stable_gclk $steady_gclk $stime $stop $strobe $strobeb $strobeh $strobeo $swrite $sync$and$array $sync$and$plane $sync$nand$array $sync$nand$plane $sync$nor$array $sync$nor$plane $sync$or$array $sync$or$plane $system $tan $tanh $test$plusargs $time $timeformat $timescale $timeskew $typename $typeof $uandom $ungetc $unit $unpacked_dimensions $unsigned $upscope $urandom_range $value$plusargs $var $vcdclose $version $warning $width $write $writeb $writeh $writememb $writememh $writeo";
// color text
static SScintillaColors g_rgb_Syntax_verilog[] =
{ {} };

//--------------------------------
//---- vhdl Language
//--------------------------------
// language
static CString g_str_vhdl_language = _T("vhdl");
// extentions
static CString g_str_vhdl_extention = _T("vhdl");
// comment line
static CString g_str_vhdl_commentline = _T("--");
// comment start
static CString g_str_vhdl_commentStart = _T("");
// comment end
static CString g_str_vhdl_commentEnd = _T("");
// keywords
static const char* g_vhdl_KeyWords =
"access after alias all architecture array assert attribute begin block body buffer bus case component configuration constant disconnect downto else elsif end entity exit file for function generate generic group guarded if impure in inertial inout is label library linkage literal loop map new next null of on open others out package port postponed procedure process pure range record register reject report return select severity shared signal subtype then to transport type unaffected units until use variable wait when while with assume assume_guarantee context cover default fairness force parameter property protected release restrict restrict_guarantee sequence strong vmode vprop vunit"
"abs and mod nand nor not or rem rol ror sla sll sra srl xnor xor"
"left right low high ascending image value pos val succ pred leftof rightof base range reverse_range length delayed stable quiet transaction event active last_event last_active last_value driving driving_value simple_name path_name instance_name"
"now readline read writeline write endfile resolved to_bit to_bitvector to_stdulogic to_stdlogicvector to_stdulogicvector to_x01 to_x01z to_UX01 rising_edge falling_edge is_x shift_left shift_right rotate_left rotate_right resize to_integer to_unsigned to_signed std_match to_01"
"std ieee work standard textio std_logic_1164 std_logic_arith std_logic_misc std_logic_signed std_logic_textio std_logic_unsigned numeric_bit numeric_std math_complex math_real vital_primitives vital_timing"
"boolean bit character severity_level integer real time delay_length natural positive string bit_vector file_open_kind file_open_status line text side width std_ulogic std_ulogic_vector std_logic std_logic_vector X01 X01Z UX01 UX01Z unsigned signed"
"boolean bit character severity_level integer real time delay_length natural positive string bit_vector file_open_kind file_open_status line text side width std_ulogic std_ulogic_vector std_logic std_logic_vector X01 X01Z UX01 UX01Z unsigned signed";
// color text
static SScintillaColors g_rgb_Syntax_vhdl[] =
{ {} };

//--------------------------------
//---- visualprolog Language
//--------------------------------
// language
static CString g_str_visualprolog_language = _T("visualprolog");
// extentions
static CString g_str_visualprolog_extention = _T("visualprolog");
// comment line
static CString g_str_visualprolog_commentline = _T("%");
// comment start
static CString g_str_visualprolog_commentStart = _T("/*");
// comment end
static CString g_str_visualprolog_commentEnd = _T("*/");
// keywords
static const char* g_visualprolog_KeyWords =
"goal namespace interface class implement open inherits supports resolve delegate monitor constants domains predicates constructors properties clauses facts"
"guard language stdcall apicall c thiscall prolog digits if then elseif else foreach do try catch finally erroneous failure procedure determ multi nondeterm anyflow and or externally from div mod rem quot in orelse otherwise"
"include bininclude requires orrequires if then else elseif endif error message export externally options"
"short detail end exception withdomain"
"short detail end exception withdomain";
// color text
static SScintillaColors g_rgb_Syntax_visualprolog[] =
{ {} };

//--------------------------------
//---- xml Language
//--------------------------------
// language
static CString g_str_xml_language = _T("xml");
// extentions
static CString g_str_xml_extention = _T("xml");
// comment line
static CString g_str_xml_commentline = _T("");
// comment start
static CString g_str_xml_commentStart = _T("<!--");
// comment end
static CString g_str_xml_commentEnd = _T("-->");
// keywords
static const char* g_xml_KeyWords =
// color text
static SScintillaColors g_rgb_Syntax_xml[] =
{ {} };

//--------------------------------
//---- yaml Language
//--------------------------------
// language
static CString g_str_yaml_language = _T("yaml");
// extentions
static CString g_str_yaml_extention = _T("yaml");
// comment line
static CString g_str_yaml_commentline = _T("#");
// comment start
static CString g_str_yaml_commentStart = _T("");
// comment end
static CString g_str_yaml_commentEnd = _T("");
// keywords
static const char* g_yaml_KeyWords =
"true false yes no"
"true false yes no";
// color text
static SScintillaColors g_rgb_Syntax_yaml[] =
{ {} };

//--------------------------------
//---- searchResult Language
//--------------------------------
// language
static CString g_str_searchResult_language = _T("searchResult");
// extentions
static CString g_str_searchResult_extention = _T("searchResult");
// comment line
static CString g_str_searchResult_commentline = _T("");
// comment start
static CString g_str_searchResult_commentStart = _T("");
// comment end
static CString g_str_searchResult_commentEnd = _T("");
// keywords
static const char* g_searchResult_KeyWords =
""
""
""
"";
// color text
static SScintillaColors g_rgb_Syntax_searchResult[] =
{ {} };

//----------------------------------------------------------------
void CScintillaEditor::Init_normal_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_NORMAL);
	SetKeywords(ScinRules::g_normal_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_normal[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_normal[i].iItem, ScinRules::g_rgb_Syntax_normal[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_normal_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_normal_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_normal_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_normal_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_normal_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_normal_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_actionscript_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_ACTIONSCRIPT);
	SetKeywords(ScinRules::g_actionscript_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_actionscript[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_actionscript[i].iItem, ScinRules::g_rgb_Syntax_actionscript[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_actionscript_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_actionscript_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_actionscript_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_actionscript_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_actionscript_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_actionscript_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_ada_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_ADA);
	SetKeywords(ScinRules::g_ada_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_ada[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_ada[i].iItem, ScinRules::g_rgb_Syntax_ada[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_ada_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_ada_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_ada_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_ada_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_ada_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_ada_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_asm_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_ASM);
	SetKeywords(ScinRules::g_asm_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_asm[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_asm[i].iItem, ScinRules::g_rgb_Syntax_asm[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_asm_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_asm_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_asm_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_asm_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_asm_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_asm_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_asn1_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_ASN1);
	SetKeywords(ScinRules::g_asn1_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_asn1[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_asn1[i].iItem, ScinRules::g_rgb_Syntax_asn1[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_asn1_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_asn1_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_asn1_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_asn1_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_asn1_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_asn1_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_asp_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_ASP);
	SetKeywords(ScinRules::g_asp_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_asp[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_asp[i].iItem, ScinRules::g_rgb_Syntax_asp[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_asp_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_asp_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_asp_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_asp_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_asp_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_asp_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_autoit_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_AUTOIT);
	SetKeywords(ScinRules::g_autoit_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_autoit[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_autoit[i].iItem, ScinRules::g_rgb_Syntax_autoit[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_autoit_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_autoit_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_autoit_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_autoit_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_autoit_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_autoit_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_avs_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_AVS);
	SetKeywords(ScinRules::g_avs_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_avs[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_avs[i].iItem, ScinRules::g_rgb_Syntax_avs[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_avs_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_avs_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_avs_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_avs_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_avs_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_avs_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_baanc_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_BAANC);
	SetKeywords(ScinRules::g_baanc_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_baanc[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_baanc[i].iItem, ScinRules::g_rgb_Syntax_baanc[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_baanc_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_baanc_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_baanc_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_baanc_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_baanc_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_baanc_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_bash_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_BASH);
	SetKeywords(ScinRules::g_bash_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_bash[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_bash[i].iItem, ScinRules::g_rgb_Syntax_bash[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_bash_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_bash_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_bash_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_bash_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_bash_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_bash_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_batch_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_BATCH);
	SetKeywords(ScinRules::g_batch_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_batch[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_batch[i].iItem, ScinRules::g_rgb_Syntax_batch[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_batch_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_batch_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_batch_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_batch_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_batch_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_batch_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_blitzbasic_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_BLITZBASIC);
	SetKeywords(ScinRules::g_blitzbasic_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_blitzbasic[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_blitzbasic[i].iItem, ScinRules::g_rgb_Syntax_blitzbasic[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_blitzbasic_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_blitzbasic_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_blitzbasic_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_blitzbasic_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_blitzbasic_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_blitzbasic_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_c_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_C);
	SetKeywords(ScinRules::g_c_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_c[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_c[i].iItem, ScinRules::g_rgb_Syntax_c[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_c_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_c_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_c_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_c_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_c_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_c_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_caml_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_CAML);
	SetKeywords(ScinRules::g_caml_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_caml[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_caml[i].iItem, ScinRules::g_rgb_Syntax_caml[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_caml_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_caml_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_caml_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_caml_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_caml_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_caml_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_cmake_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_CMAKE);
	SetKeywords(ScinRules::g_cmake_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_cmake[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_cmake[i].iItem, ScinRules::g_rgb_Syntax_cmake[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_cmake_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_cmake_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_cmake_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_cmake_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_cmake_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_cmake_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_cobol_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_COBOL);
	SetKeywords(ScinRules::g_cobol_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_cobol[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_cobol[i].iItem, ScinRules::g_rgb_Syntax_cobol[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_cobol_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_cobol_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_cobol_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_cobol_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_cobol_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_cobol_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_csound_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_CSOUND);
	SetKeywords(ScinRules::g_csound_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_csound[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_csound[i].iItem, ScinRules::g_rgb_Syntax_csound[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_csound_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_csound_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_csound_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_csound_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_csound_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_csound_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_coffeescript_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_COFFEESCRIPT);
	SetKeywords(ScinRules::g_coffeescript_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_coffeescript[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_coffeescript[i].iItem, ScinRules::g_rgb_Syntax_coffeescript[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_coffeescript_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_coffeescript_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_coffeescript_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_coffeescript_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_coffeescript_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_coffeescript_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_cpp_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_CPP);
	SetKeywords(ScinRules::g_cpp_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_cpp[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_cpp[i].iItem, ScinRules::g_rgb_Syntax_cpp[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_cpp_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_cpp_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_cpp_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_cpp_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_cpp_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_cpp_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_cs_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_CS);
	SetKeywords(ScinRules::g_cs_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_cs[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_cs[i].iItem, ScinRules::g_rgb_Syntax_cs[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_cs_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_cs_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_cs_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_cs_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_cs_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_cs_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_css_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_CSS);
	SetKeywords(ScinRules::g_css_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_css[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_css[i].iItem, ScinRules::g_rgb_Syntax_css[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_css_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_css_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_css_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_css_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_css_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_css_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_d_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_D);
	SetKeywords(ScinRules::g_d_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_d[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_d[i].iItem, ScinRules::g_rgb_Syntax_d[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_d_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_d_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_d_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_d_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_d_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_d_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_diff_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_DIFF);
	SetKeywords(ScinRules::g_diff_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_diff[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_diff[i].iItem, ScinRules::g_rgb_Syntax_diff[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_diff_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_diff_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_diff_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_diff_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_diff_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_diff_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_erlang_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_ERLANG);
	SetKeywords(ScinRules::g_erlang_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_erlang[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_erlang[i].iItem, ScinRules::g_rgb_Syntax_erlang[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_erlang_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_erlang_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_erlang_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_erlang_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_erlang_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_erlang_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_escript_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_ESCRIPT);
	SetKeywords(ScinRules::g_escript_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_escript[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_escript[i].iItem, ScinRules::g_rgb_Syntax_escript[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_escript_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_escript_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_escript_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_escript_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_escript_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_escript_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_forth_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_FORTH);
	SetKeywords(ScinRules::g_forth_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_forth[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_forth[i].iItem, ScinRules::g_rgb_Syntax_forth[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_forth_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_forth_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_forth_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_forth_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_forth_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_forth_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_fortran_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_FORTRAN);
	SetKeywords(ScinRules::g_fortran_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_fortran[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_fortran[i].iItem, ScinRules::g_rgb_Syntax_fortran[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_fortran_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_fortran_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_fortran_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_fortran_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_fortran_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_fortran_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_fortran77_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_FORTRAN77);
	SetKeywords(ScinRules::g_fortran77_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_fortran77[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_fortran77[i].iItem, ScinRules::g_rgb_Syntax_fortran77[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_fortran77_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_fortran77_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_fortran77_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_fortran77_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_fortran77_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_fortran77_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_freebasic_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_FREEBASIC);
	SetKeywords(ScinRules::g_freebasic_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_freebasic[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_freebasic[i].iItem, ScinRules::g_rgb_Syntax_freebasic[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_freebasic_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_freebasic_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_freebasic_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_freebasic_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_freebasic_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_freebasic_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_gui4cli_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_GUI4CLI);
	SetKeywords(ScinRules::g_gui4cli_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_gui4cli[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_gui4cli[i].iItem, ScinRules::g_rgb_Syntax_gui4cli[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_gui4cli_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_gui4cli_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_gui4cli_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_gui4cli_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_gui4cli_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_gui4cli_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_haskell_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_HASKELL);
	SetKeywords(ScinRules::g_haskell_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_haskell[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_haskell[i].iItem, ScinRules::g_rgb_Syntax_haskell[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_haskell_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_haskell_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_haskell_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_haskell_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_haskell_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_haskell_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_html_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_HTML);
	SetKeywords(ScinRules::g_html_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_html[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_html[i].iItem, ScinRules::g_rgb_Syntax_html[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_html_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_html_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_html_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_html_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_html_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_html_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_ini_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_INI);
	SetKeywords(ScinRules::g_ini_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_ini[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_ini[i].iItem, ScinRules::g_rgb_Syntax_ini[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_ini_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_ini_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_ini_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_ini_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_ini_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_ini_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_inno_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_INNO);
	SetKeywords(ScinRules::g_inno_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_inno[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_inno[i].iItem, ScinRules::g_rgb_Syntax_inno[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_inno_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_inno_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_inno_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_inno_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_inno_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_inno_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_ihex_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_IHEX);
	SetKeywords(ScinRules::g_ihex_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_ihex[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_ihex[i].iItem, ScinRules::g_rgb_Syntax_ihex[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_ihex_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_ihex_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_ihex_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_ihex_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_ihex_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_ihex_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_java_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_JAVA);
	SetKeywords(ScinRules::g_java_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_java[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_java[i].iItem, ScinRules::g_rgb_Syntax_java[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_java_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_java_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_java_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_java_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_java_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_java_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_javascript_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_JAVASCRIPT);
	SetKeywords(ScinRules::g_javascript_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_javascript[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_javascript[i].iItem, ScinRules::g_rgb_Syntax_javascript[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_javascript_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_javascript_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_javascript_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_javascript_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_javascript_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_javascript_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_javascript.js_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_JAVASCRIPT.JS);
	SetKeywords(ScinRules::g_javascript.js_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_javascript.js[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_javascript.js[i].iItem, ScinRules::g_rgb_Syntax_javascript.js[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_javascript.js_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_javascript.js_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_javascript.js_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_javascript.js_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_javascript.js_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_javascript.js_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_json_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_JSON);
	SetKeywords(ScinRules::g_json_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_json[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_json[i].iItem, ScinRules::g_rgb_Syntax_json[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_json_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_json_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_json_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_json_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_json_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_json_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_jsp_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_JSP);
	SetKeywords(ScinRules::g_jsp_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_jsp[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_jsp[i].iItem, ScinRules::g_rgb_Syntax_jsp[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_jsp_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_jsp_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_jsp_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_jsp_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_jsp_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_jsp_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_kix_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_KIX);
	SetKeywords(ScinRules::g_kix_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_kix[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_kix[i].iItem, ScinRules::g_rgb_Syntax_kix[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_kix_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_kix_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_kix_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_kix_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_kix_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_kix_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_lisp_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_LISP);
	SetKeywords(ScinRules::g_lisp_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_lisp[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_lisp[i].iItem, ScinRules::g_rgb_Syntax_lisp[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_lisp_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_lisp_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_lisp_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_lisp_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_lisp_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_lisp_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_latex_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_LATEX);
	SetKeywords(ScinRules::g_latex_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_latex[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_latex[i].iItem, ScinRules::g_rgb_Syntax_latex[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_latex_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_latex_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_latex_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_latex_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_latex_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_latex_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_lua_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_LUA);
	SetKeywords(ScinRules::g_lua_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_lua[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_lua[i].iItem, ScinRules::g_rgb_Syntax_lua[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_lua_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_lua_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_lua_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_lua_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_lua_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_lua_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_makefile_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_MAKEFILE);
	SetKeywords(ScinRules::g_makefile_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_makefile[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_makefile[i].iItem, ScinRules::g_rgb_Syntax_makefile[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_makefile_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_makefile_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_makefile_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_makefile_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_makefile_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_makefile_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_matlab_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_MATLAB);
	SetKeywords(ScinRules::g_matlab_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_matlab[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_matlab[i].iItem, ScinRules::g_rgb_Syntax_matlab[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_matlab_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_matlab_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_matlab_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_matlab_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_matlab_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_matlab_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_mmixal_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_MMIXAL);
	SetKeywords(ScinRules::g_mmixal_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_mmixal[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_mmixal[i].iItem, ScinRules::g_rgb_Syntax_mmixal[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_mmixal_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_mmixal_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_mmixal_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_mmixal_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_mmixal_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_mmixal_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_nimrod_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_NIMROD);
	SetKeywords(ScinRules::g_nimrod_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_nimrod[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_nimrod[i].iItem, ScinRules::g_rgb_Syntax_nimrod[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_nimrod_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_nimrod_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_nimrod_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_nimrod_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_nimrod_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_nimrod_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_nncrontab_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_NNCRONTAB);
	SetKeywords(ScinRules::g_nncrontab_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_nncrontab[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_nncrontab[i].iItem, ScinRules::g_rgb_Syntax_nncrontab[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_nncrontab_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_nncrontab_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_nncrontab_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_nncrontab_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_nncrontab_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_nncrontab_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_nfo_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_NFO);
	SetKeywords(ScinRules::g_nfo_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_nfo[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_nfo[i].iItem, ScinRules::g_rgb_Syntax_nfo[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_nfo_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_nfo_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_nfo_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_nfo_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_nfo_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_nfo_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_nsis_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_NSIS);
	SetKeywords(ScinRules::g_nsis_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_nsis[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_nsis[i].iItem, ScinRules::g_rgb_Syntax_nsis[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_nsis_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_nsis_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_nsis_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_nsis_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_nsis_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_nsis_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_oscript_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_OSCRIPT);
	SetKeywords(ScinRules::g_oscript_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_oscript[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_oscript[i].iItem, ScinRules::g_rgb_Syntax_oscript[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_oscript_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_oscript_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_oscript_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_oscript_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_oscript_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_oscript_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_objc_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_OBJC);
	SetKeywords(ScinRules::g_objc_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_objc[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_objc[i].iItem, ScinRules::g_rgb_Syntax_objc[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_objc_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_objc_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_objc_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_objc_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_objc_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_objc_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_pascal_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_PASCAL);
	SetKeywords(ScinRules::g_pascal_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_pascal[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_pascal[i].iItem, ScinRules::g_rgb_Syntax_pascal[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_pascal_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_pascal_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_pascal_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_pascal_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_pascal_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_pascal_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_perl_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_PERL);
	SetKeywords(ScinRules::g_perl_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_perl[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_perl[i].iItem, ScinRules::g_rgb_Syntax_perl[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_perl_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_perl_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_perl_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_perl_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_perl_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_perl_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_php_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_PHP);
	SetKeywords(ScinRules::g_php_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_php[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_php[i].iItem, ScinRules::g_rgb_Syntax_php[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_php_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_php_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_php_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_php_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_php_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_php_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_postscript_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_POSTSCRIPT);
	SetKeywords(ScinRules::g_postscript_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_postscript[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_postscript[i].iItem, ScinRules::g_rgb_Syntax_postscript[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_postscript_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_postscript_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_postscript_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_postscript_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_postscript_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_postscript_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_powershell_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_POWERSHELL);
	SetKeywords(ScinRules::g_powershell_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_powershell[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_powershell[i].iItem, ScinRules::g_rgb_Syntax_powershell[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_powershell_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_powershell_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_powershell_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_powershell_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_powershell_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_powershell_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_props_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_PROPS);
	SetKeywords(ScinRules::g_props_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_props[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_props[i].iItem, ScinRules::g_rgb_Syntax_props[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_props_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_props_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_props_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_props_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_props_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_props_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_purebasic_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_PUREBASIC);
	SetKeywords(ScinRules::g_purebasic_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_purebasic[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_purebasic[i].iItem, ScinRules::g_rgb_Syntax_purebasic[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_purebasic_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_purebasic_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_purebasic_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_purebasic_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_purebasic_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_purebasic_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_python_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_PYTHON);
	SetKeywords(ScinRules::g_python_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_python[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_python[i].iItem, ScinRules::g_rgb_Syntax_python[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_python_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_python_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_python_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_python_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_python_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_python_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_r_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_R);
	SetKeywords(ScinRules::g_r_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_r[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_r[i].iItem, ScinRules::g_rgb_Syntax_r[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_r_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_r_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_r_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_r_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_r_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_r_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_rebol_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_REBOL);
	SetKeywords(ScinRules::g_rebol_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_rebol[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_rebol[i].iItem, ScinRules::g_rgb_Syntax_rebol[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_rebol_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_rebol_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_rebol_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_rebol_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_rebol_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_rebol_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_registry_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_REGISTRY);
	SetKeywords(ScinRules::g_registry_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_registry[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_registry[i].iItem, ScinRules::g_rgb_Syntax_registry[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_registry_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_registry_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_registry_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_registry_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_registry_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_registry_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_rc_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_RC);
	SetKeywords(ScinRules::g_rc_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_rc[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_rc[i].iItem, ScinRules::g_rgb_Syntax_rc[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_rc_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_rc_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_rc_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_rc_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_rc_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_rc_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_ruby_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_RUBY);
	SetKeywords(ScinRules::g_ruby_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_ruby[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_ruby[i].iItem, ScinRules::g_rgb_Syntax_ruby[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_ruby_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_ruby_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_ruby_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_ruby_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_ruby_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_ruby_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_rust_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_RUST);
	SetKeywords(ScinRules::g_rust_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_rust[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_rust[i].iItem, ScinRules::g_rgb_Syntax_rust[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_rust_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_rust_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_rust_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_rust_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_rust_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_rust_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_scheme_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_SCHEME);
	SetKeywords(ScinRules::g_scheme_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_scheme[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_scheme[i].iItem, ScinRules::g_rgb_Syntax_scheme[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_scheme_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_scheme_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_scheme_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_scheme_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_scheme_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_scheme_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_smalltalk_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_SMALLTALK);
	SetKeywords(ScinRules::g_smalltalk_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_smalltalk[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_smalltalk[i].iItem, ScinRules::g_rgb_Syntax_smalltalk[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_smalltalk_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_smalltalk_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_smalltalk_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_smalltalk_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_smalltalk_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_smalltalk_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_spice_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_SPICE);
	SetKeywords(ScinRules::g_spice_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_spice[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_spice[i].iItem, ScinRules::g_rgb_Syntax_spice[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_spice_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_spice_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_spice_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_spice_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_spice_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_spice_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_sql_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_SQL);
	SetKeywords(ScinRules::g_sql_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_sql[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_sql[i].iItem, ScinRules::g_rgb_Syntax_sql[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_sql_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_sql_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_sql_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_sql_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_sql_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_sql_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_srec_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_SREC);
	SetKeywords(ScinRules::g_srec_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_srec[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_srec[i].iItem, ScinRules::g_rgb_Syntax_srec[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_srec_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_srec_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_srec_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_srec_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_srec_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_srec_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_swift_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_SWIFT);
	SetKeywords(ScinRules::g_swift_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_swift[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_swift[i].iItem, ScinRules::g_rgb_Syntax_swift[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_swift_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_swift_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_swift_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_swift_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_swift_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_swift_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_tcl_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_TCL);
	SetKeywords(ScinRules::g_tcl_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_tcl[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_tcl[i].iItem, ScinRules::g_rgb_Syntax_tcl[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_tcl_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_tcl_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_tcl_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_tcl_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_tcl_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_tcl_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_tehex_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_TEHEX);
	SetKeywords(ScinRules::g_tehex_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_tehex[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_tehex[i].iItem, ScinRules::g_rgb_Syntax_tehex[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_tehex_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_tehex_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_tehex_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_tehex_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_tehex_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_tehex_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_tex_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_TEX);
	SetKeywords(ScinRules::g_tex_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_tex[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_tex[i].iItem, ScinRules::g_rgb_Syntax_tex[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_tex_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_tex_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_tex_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_tex_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_tex_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_tex_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_vb_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_VB);
	SetKeywords(ScinRules::g_vb_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_vb[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_vb[i].iItem, ScinRules::g_rgb_Syntax_vb[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_vb_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_vb_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_vb_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_vb_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_vb_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_vb_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_txt2tags_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_TXT2TAGS);
	SetKeywords(ScinRules::g_txt2tags_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_txt2tags[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_txt2tags[i].iItem, ScinRules::g_rgb_Syntax_txt2tags[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_txt2tags_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_txt2tags_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_txt2tags_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_txt2tags_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_txt2tags_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_txt2tags_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_verilog_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_VERILOG);
	SetKeywords(ScinRules::g_verilog_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_verilog[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_verilog[i].iItem, ScinRules::g_rgb_Syntax_verilog[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_verilog_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_verilog_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_verilog_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_verilog_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_verilog_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_verilog_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_vhdl_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_VHDL);
	SetKeywords(ScinRules::g_vhdl_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_vhdl[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_vhdl[i].iItem, ScinRules::g_rgb_Syntax_vhdl[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_vhdl_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_vhdl_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_vhdl_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_vhdl_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_vhdl_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_vhdl_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_visualprolog_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_VISUALPROLOG);
	SetKeywords(ScinRules::g_visualprolog_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_visualprolog[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_visualprolog[i].iItem, ScinRules::g_rgb_Syntax_visualprolog[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_visualprolog_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_visualprolog_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_visualprolog_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_visualprolog_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_visualprolog_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_visualprolog_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_xml_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_XML);
	SetKeywords(ScinRules::g_xml_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_xml[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_xml[i].iItem, ScinRules::g_rgb_Syntax_xml[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_xml_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_xml_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_xml_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_xml_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_xml_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_xml_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_yaml_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_YAML);
	SetKeywords(ScinRules::g_yaml_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_yaml[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_yaml[i].iItem, ScinRules::g_rgb_Syntax_yaml[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_yaml_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_yaml_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_yaml_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_yaml_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_yaml_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_yaml_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
void CScintillaEditor::Init_searchResult_Editor(CIDEDatabase* pDatabase)
{
	SetLexer(SCLEX_SEARCHRESULT);
	SetKeywords(ScinRules::g_searchresult_KeyWords);
	for (long i = 0; ScinRules::g_rgb_Syntax_searchresult[i].iItem != -1; i++) {
		SetAStyle(ScinRules::g_rgb_Syntax_searchresult[i].iItem, ScinRules::g_rgb_Syntax_searchresult[i].rgb);
	pDatabase->SetLanguageName(ScinRules::g_str_searchresult_language);
	pDatabase->SetLanguageExtension(ScinRules::g_str_searchresult_extention);
	pDatabase->SetLanguageCommentLine(ScinRules::g_str_searchresult_commentline);
	pDatabase->SetLanguageCommentStart(ScinRules::g_str_searchresult_commentStart);
	pDatabase->SetLanguageCommentEnd(ScinRules::g_str_searchresult_commentEnd);
	CString strKeywords = IDEUtil::StdToCString(ScinRules::g_searchresult_KeyWords);
	pDatabase->SetLanguageKeyWords(strKeywords);
	}
}
//----------------------------------------------------------------
void Init_normal_Editor(CIDEDatabase* pDatabase);
void Init_actionscript_Editor(CIDEDatabase* pDatabase);
void Init_ada_Editor(CIDEDatabase* pDatabase);
void Init_asm_Editor(CIDEDatabase* pDatabase);
void Init_asn1_Editor(CIDEDatabase* pDatabase);
void Init_asp_Editor(CIDEDatabase* pDatabase);
void Init_autoit_Editor(CIDEDatabase* pDatabase);
void Init_avs_Editor(CIDEDatabase* pDatabase);
void Init_baanc_Editor(CIDEDatabase* pDatabase);
void Init_bash_Editor(CIDEDatabase* pDatabase);
void Init_batch_Editor(CIDEDatabase* pDatabase);
void Init_blitzbasic_Editor(CIDEDatabase* pDatabase);
void Init_c_Editor(CIDEDatabase* pDatabase);
void Init_caml_Editor(CIDEDatabase* pDatabase);
void Init_cmake_Editor(CIDEDatabase* pDatabase);
void Init_cobol_Editor(CIDEDatabase* pDatabase);
void Init_csound_Editor(CIDEDatabase* pDatabase);
void Init_coffeescript_Editor(CIDEDatabase* pDatabase);
void Init_cpp_Editor(CIDEDatabase* pDatabase);
void Init_cs_Editor(CIDEDatabase* pDatabase);
void Init_css_Editor(CIDEDatabase* pDatabase);
void Init_d_Editor(CIDEDatabase* pDatabase);
void Init_diff_Editor(CIDEDatabase* pDatabase);
void Init_erlang_Editor(CIDEDatabase* pDatabase);
void Init_escript_Editor(CIDEDatabase* pDatabase);
void Init_forth_Editor(CIDEDatabase* pDatabase);
void Init_fortran_Editor(CIDEDatabase* pDatabase);
void Init_fortran77_Editor(CIDEDatabase* pDatabase);
void Init_freebasic_Editor(CIDEDatabase* pDatabase);
void Init_gui4cli_Editor(CIDEDatabase* pDatabase);
void Init_haskell_Editor(CIDEDatabase* pDatabase);
void Init_html_Editor(CIDEDatabase* pDatabase);
void Init_ini_Editor(CIDEDatabase* pDatabase);
void Init_inno_Editor(CIDEDatabase* pDatabase);
void Init_ihex_Editor(CIDEDatabase* pDatabase);
void Init_java_Editor(CIDEDatabase* pDatabase);
void Init_javascript_Editor(CIDEDatabase* pDatabase);
void Init_javascript.js_Editor(CIDEDatabase* pDatabase);
void Init_json_Editor(CIDEDatabase* pDatabase);
void Init_jsp_Editor(CIDEDatabase* pDatabase);
void Init_kix_Editor(CIDEDatabase* pDatabase);
void Init_lisp_Editor(CIDEDatabase* pDatabase);
void Init_latex_Editor(CIDEDatabase* pDatabase);
void Init_lua_Editor(CIDEDatabase* pDatabase);
void Init_makefile_Editor(CIDEDatabase* pDatabase);
void Init_matlab_Editor(CIDEDatabase* pDatabase);
void Init_mmixal_Editor(CIDEDatabase* pDatabase);
void Init_nimrod_Editor(CIDEDatabase* pDatabase);
void Init_nncrontab_Editor(CIDEDatabase* pDatabase);
void Init_nfo_Editor(CIDEDatabase* pDatabase);
void Init_nsis_Editor(CIDEDatabase* pDatabase);
void Init_oscript_Editor(CIDEDatabase* pDatabase);
void Init_objc_Editor(CIDEDatabase* pDatabase);
void Init_pascal_Editor(CIDEDatabase* pDatabase);
void Init_perl_Editor(CIDEDatabase* pDatabase);
void Init_php_Editor(CIDEDatabase* pDatabase);
void Init_postscript_Editor(CIDEDatabase* pDatabase);
void Init_powershell_Editor(CIDEDatabase* pDatabase);
void Init_props_Editor(CIDEDatabase* pDatabase);
void Init_purebasic_Editor(CIDEDatabase* pDatabase);
void Init_python_Editor(CIDEDatabase* pDatabase);
void Init_r_Editor(CIDEDatabase* pDatabase);
void Init_rebol_Editor(CIDEDatabase* pDatabase);
void Init_registry_Editor(CIDEDatabase* pDatabase);
void Init_rc_Editor(CIDEDatabase* pDatabase);
void Init_ruby_Editor(CIDEDatabase* pDatabase);
void Init_rust_Editor(CIDEDatabase* pDatabase);
void Init_scheme_Editor(CIDEDatabase* pDatabase);
void Init_smalltalk_Editor(CIDEDatabase* pDatabase);
void Init_spice_Editor(CIDEDatabase* pDatabase);
void Init_sql_Editor(CIDEDatabase* pDatabase);
void Init_srec_Editor(CIDEDatabase* pDatabase);
void Init_swift_Editor(CIDEDatabase* pDatabase);
void Init_tcl_Editor(CIDEDatabase* pDatabase);
void Init_tehex_Editor(CIDEDatabase* pDatabase);
void Init_tex_Editor(CIDEDatabase* pDatabase);
void Init_vb_Editor(CIDEDatabase* pDatabase);
void Init_txt2tags_Editor(CIDEDatabase* pDatabase);
void Init_verilog_Editor(CIDEDatabase* pDatabase);
void Init_vhdl_Editor(CIDEDatabase* pDatabase);
void Init_visualprolog_Editor(CIDEDatabase* pDatabase);
void Init_xml_Editor(CIDEDatabase* pDatabase);
void Init_yaml_Editor(CIDEDatabase* pDatabase);
void Init_searchResult_Editor(CIDEDatabase* pDatabase);
//----------------------------------------------------------------
	case SCLEX_NORMAL:
		Init_normal_Editor(pDatabase);
		break;
	case SCLEX_ACTIONSCRIPT:
		Init_actionscript_Editor(pDatabase);
		break;
	case SCLEX_ADA:
		Init_ada_Editor(pDatabase);
		break;
	case SCLEX_ASM:
		Init_asm_Editor(pDatabase);
		break;
	case SCLEX_ASN1:
		Init_asn1_Editor(pDatabase);
		break;
	case SCLEX_ASP:
		Init_asp_Editor(pDatabase);
		break;
	case SCLEX_AUTOIT:
		Init_autoit_Editor(pDatabase);
		break;
	case SCLEX_AVS:
		Init_avs_Editor(pDatabase);
		break;
	case SCLEX_BAANC:
		Init_baanc_Editor(pDatabase);
		break;
	case SCLEX_BASH:
		Init_bash_Editor(pDatabase);
		break;
	case SCLEX_BATCH:
		Init_batch_Editor(pDatabase);
		break;
	case SCLEX_BLITZBASIC:
		Init_blitzbasic_Editor(pDatabase);
		break;
	case SCLEX_C:
		Init_c_Editor(pDatabase);
		break;
	case SCLEX_CAML:
		Init_caml_Editor(pDatabase);
		break;
	case SCLEX_CMAKE:
		Init_cmake_Editor(pDatabase);
		break;
	case SCLEX_COBOL:
		Init_cobol_Editor(pDatabase);
		break;
	case SCLEX_CSOUND:
		Init_csound_Editor(pDatabase);
		break;
	case SCLEX_COFFEESCRIPT:
		Init_coffeescript_Editor(pDatabase);
		break;
	case SCLEX_CPP:
		Init_cpp_Editor(pDatabase);
		break;
	case SCLEX_CS:
		Init_cs_Editor(pDatabase);
		break;
	case SCLEX_CSS:
		Init_css_Editor(pDatabase);
		break;
	case SCLEX_D:
		Init_d_Editor(pDatabase);
		break;
	case SCLEX_DIFF:
		Init_diff_Editor(pDatabase);
		break;
	case SCLEX_ERLANG:
		Init_erlang_Editor(pDatabase);
		break;
	case SCLEX_ESCRIPT:
		Init_escript_Editor(pDatabase);
		break;
	case SCLEX_FORTH:
		Init_forth_Editor(pDatabase);
		break;
	case SCLEX_FORTRAN:
		Init_fortran_Editor(pDatabase);
		break;
	case SCLEX_FORTRAN77:
		Init_fortran77_Editor(pDatabase);
		break;
	case SCLEX_FREEBASIC:
		Init_freebasic_Editor(pDatabase);
		break;
	case SCLEX_GUI4CLI:
		Init_gui4cli_Editor(pDatabase);
		break;
	case SCLEX_HASKELL:
		Init_haskell_Editor(pDatabase);
		break;
	case SCLEX_HTML:
		Init_html_Editor(pDatabase);
		break;
	case SCLEX_INI:
		Init_ini_Editor(pDatabase);
		break;
	case SCLEX_INNO:
		Init_inno_Editor(pDatabase);
		break;
	case SCLEX_IHEX:
		Init_ihex_Editor(pDatabase);
		break;
	case SCLEX_JAVA:
		Init_java_Editor(pDatabase);
		break;
	case SCLEX_JAVASCRIPT:
		Init_javascript_Editor(pDatabase);
		break;
	case SCLEX_JAVASCRIPT.JS:
		Init_javascript.js_Editor(pDatabase);
		break;
	case SCLEX_JSON:
		Init_json_Editor(pDatabase);
		break;
	case SCLEX_JSP:
		Init_jsp_Editor(pDatabase);
		break;
	case SCLEX_KIX:
		Init_kix_Editor(pDatabase);
		break;
	case SCLEX_LISP:
		Init_lisp_Editor(pDatabase);
		break;
	case SCLEX_LATEX:
		Init_latex_Editor(pDatabase);
		break;
	case SCLEX_LUA:
		Init_lua_Editor(pDatabase);
		break;
	case SCLEX_MAKEFILE:
		Init_makefile_Editor(pDatabase);
		break;
	case SCLEX_MATLAB:
		Init_matlab_Editor(pDatabase);
		break;
	case SCLEX_MMIXAL:
		Init_mmixal_Editor(pDatabase);
		break;
	case SCLEX_NIMROD:
		Init_nimrod_Editor(pDatabase);
		break;
	case SCLEX_NNCRONTAB:
		Init_nncrontab_Editor(pDatabase);
		break;
	case SCLEX_NFO:
		Init_nfo_Editor(pDatabase);
		break;
	case SCLEX_NSIS:
		Init_nsis_Editor(pDatabase);
		break;
	case SCLEX_OSCRIPT:
		Init_oscript_Editor(pDatabase);
		break;
	case SCLEX_OBJC:
		Init_objc_Editor(pDatabase);
		break;
	case SCLEX_PASCAL:
		Init_pascal_Editor(pDatabase);
		break;
	case SCLEX_PERL:
		Init_perl_Editor(pDatabase);
		break;
	case SCLEX_PHP:
		Init_php_Editor(pDatabase);
		break;
	case SCLEX_POSTSCRIPT:
		Init_postscript_Editor(pDatabase);
		break;
	case SCLEX_POWERSHELL:
		Init_powershell_Editor(pDatabase);
		break;
	case SCLEX_PROPS:
		Init_props_Editor(pDatabase);
		break;
	case SCLEX_PUREBASIC:
		Init_purebasic_Editor(pDatabase);
		break;
	case SCLEX_PYTHON:
		Init_python_Editor(pDatabase);
		break;
	case SCLEX_R:
		Init_r_Editor(pDatabase);
		break;
	case SCLEX_REBOL:
		Init_rebol_Editor(pDatabase);
		break;
	case SCLEX_REGISTRY:
		Init_registry_Editor(pDatabase);
		break;
	case SCLEX_RC:
		Init_rc_Editor(pDatabase);
		break;
	case SCLEX_RUBY:
		Init_ruby_Editor(pDatabase);
		break;
	case SCLEX_RUST:
		Init_rust_Editor(pDatabase);
		break;
	case SCLEX_SCHEME:
		Init_scheme_Editor(pDatabase);
		break;
	case SCLEX_SMALLTALK:
		Init_smalltalk_Editor(pDatabase);
		break;
	case SCLEX_SPICE:
		Init_spice_Editor(pDatabase);
		break;
	case SCLEX_SQL:
		Init_sql_Editor(pDatabase);
		break;
	case SCLEX_SREC:
		Init_srec_Editor(pDatabase);
		break;
	case SCLEX_SWIFT:
		Init_swift_Editor(pDatabase);
		break;
	case SCLEX_TCL:
		Init_tcl_Editor(pDatabase);
		break;
	case SCLEX_TEHEX:
		Init_tehex_Editor(pDatabase);
		break;
	case SCLEX_TEX:
		Init_tex_Editor(pDatabase);
		break;
	case SCLEX_VB:
		Init_vb_Editor(pDatabase);
		break;
	case SCLEX_TXT2TAGS:
		Init_txt2tags_Editor(pDatabase);
		break;
	case SCLEX_VERILOG:
		Init_verilog_Editor(pDatabase);
		break;
	case SCLEX_VHDL:
		Init_vhdl_Editor(pDatabase);
		break;
	case SCLEX_VISUALPROLOG:
		Init_visualprolog_Editor(pDatabase);
		break;
	case SCLEX_XML:
		Init_xml_Editor(pDatabase);
		break;
	case SCLEX_YAML:
		Init_yaml_Editor(pDatabase);
		break;
	case SCLEX_SEARCHRESULT:
		Init_searchresult_Editor(pDatabase);
		break;
