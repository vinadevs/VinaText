// Copyright 2014 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef PUBLIC_FPDF_EDIT_H_
#define PUBLIC_FPDF_EDIT_H_

#include <stdint.h>

// NOLINTNEXTLINE(build/include)
#include "fpdfview.h"

#define FPDF_ARGB(a, r, g, b)                                      \
  ((uint32_t)(((uint32_t)(b)&0xff) | (((uint32_t)(g)&0xff) << 8) | \
              (((uint32_t)(r)&0xff) << 16) | (((uint32_t)(a)&0xff) << 24)))
#define FPDF_GetBValue(argb) ((uint8_t)(argb))
#define FPDF_GetGValue(argb) ((uint8_t)(((uint16_t)(argb)) >> 8))
#define FPDF_GetRValue(argb) ((uint8_t)((argb) >> 16))
#define FPDF_GetAValue(argb) ((uint8_t)((argb) >> 24))

// The page object constants.
#define FPDF_PAGEOBJ_UNKNOWN 0
#define FPDF_PAGEOBJ_TEXT 1
#define FPDF_PAGEOBJ_PATH 2
#define FPDF_PAGEOBJ_IMAGE 3
#define FPDF_PAGEOBJ_SHADING 4
#define FPDF_PAGEOBJ_FORM 5

#define FPDF_FILLMODE_ALTERNATE 1
#define FPDF_FILLMODE_WINDING 2

#define FPDF_FONT_TYPE1 1
#define FPDF_FONT_TRUETYPE 2

#define FPDF_LINECAP_BUTT 0
#define FPDF_LINECAP_ROUND 1
#define FPDF_LINECAP_PROJECTING_SQUARE 2

#define FPDF_LINEJOIN_MITER 0
#define FPDF_LINEJOIN_ROUND 1
#define FPDF_LINEJOIN_BEVEL 2

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

// Create a new PDF document.
//
// Returns a handle to a new document, or NULL on failure.
DLLEXPORT FPDF_DOCUMENT STDCALL FPDF_CreateNewDocument();

// Create a new PDF page.
//
//   document   - handle to document.
//   page_index - suggested index of the page to create. If it is larger than
//                document's current last index(L), the created page index is
//                the next available index -- L+1.
//   width      - the page width.
//   height     - the page height.
//
// Returns the handle to the new page.
//
// The page should be closed with CPDF_ClosePage() when finished as
// with any other page in the document.
DLLEXPORT FPDF_PAGE STDCALL FPDFPage_New(FPDF_DOCUMENT document,
                                         int page_index,
                                         double width,
                                         double height);

// Delete the page at |page_index|.
//
//   document   - handle to document.
//   page_index - the index of the page to delete.
DLLEXPORT void STDCALL FPDFPage_Delete(FPDF_DOCUMENT document, int page_index);

// Get the rotation of |page|.
//
//   page - handle to a page
//
// Returns one of the following indicating the page rotation:
//   0 - No rotation.
//   1 - Rotated 90 degrees clockwise.
//   2 - Rotated 180 degrees clockwise.
//   3 - Rotated 270 degrees clockwise.
DLLEXPORT int STDCALL FPDFPage_GetRotation(FPDF_PAGE page);

// Set rotation for |page|.
//
//   page   - handle to a page.
//   rotate - the rotation value, one of:
//              0 - No rotation.
//              1 - Rotated 90 degrees clockwise.
//              2 - Rotated 180 degrees clockwise.
//              3 - Rotated 270 degrees clockwise.
DLLEXPORT void STDCALL FPDFPage_SetRotation(FPDF_PAGE page, int rotate);

// Insert |page_obj| into |page|.
//
//   page     - handle to a page
//   page_obj - handle to a page object. The |page_obj| will be automatically
//              freed.
DLLEXPORT void STDCALL FPDFPage_InsertObject(FPDF_PAGE page,
                                             FPDF_PAGEOBJECT page_obj);

// Get number of page objects inside |page|.
//
//   page - handle to a page.
//
// Returns the number of objects in |page|.
DLLEXPORT int STDCALL FPDFPage_CountObject(FPDF_PAGE page);

// Get object in |page| at |index|.
//
//   page  - handle to a page.
//   index - the index of a page object.
//
// Returns the handle to the page object, or NULL on failed.
DLLEXPORT FPDF_PAGEOBJECT STDCALL FPDFPage_GetObject(FPDF_PAGE page, int index);

// Checks if |page| contains transparency.
//
//   page - handle to a page.
//
// Returns TRUE if |page| contains transparency.
DLLEXPORT FPDF_BOOL STDCALL FPDFPage_HasTransparency(FPDF_PAGE page);

// Generate the content of |page|.
//
//   page - handle to a page.
//
// Returns TRUE on success.
//
// Before you save the page to a file, or reload the page, you must call
// |FPDFPage_GenerateContent| or any changes to |page| will be lost.
DLLEXPORT FPDF_BOOL STDCALL FPDFPage_GenerateContent(FPDF_PAGE page);

// Checks if |pageObject| contains transparency.
//
//   pageObject - handle to a page object.
//
// Returns TRUE if |pageObject| contains transparency.
DLLEXPORT FPDF_BOOL STDCALL
FPDFPageObj_HasTransparency(FPDF_PAGEOBJECT pageObject);

// Get type of |pageObject|.
//
//   pageObject - handle to a page object.
//
// Returns one of the FPDF_PAGEOBJ_* values on success, FPDF_PAGEOBJ_UNKNOWN on
// error.
DLLEXPORT int STDCALL FPDFPageObj_GetType(FPDF_PAGEOBJECT pageObject);

// Transform |pageObject| by the given matrix.
//
//   page_object - handle to a page object.
//   a           - matrix value.
//   b           - matrix value.
//   c           - matrix value.
//   d           - matrix value.
//   e           - matrix value.
//   f           - matrix value.
//
// The matrix is composed as:
//   |a c e|
//   |b d f|
// and can be used to scale, rotate, shear and translate the |page_object|.
DLLEXPORT void STDCALL FPDFPageObj_Transform(FPDF_PAGEOBJECT page_object,
                                             double a,
                                             double b,
                                             double c,
                                             double d,
                                             double e,
                                             double f);

// Transform all annotations in |page|.
//
//   page - handle to a page.
//   a    - matrix value.
//   b    - matrix value.
//   c    - matrix value.
//   d    - matrix value.
//   e    - matrix value.
//   f    - matrix value.
//
// The matrix is composed as:
//   |a c e|
//   |b d f|
// and can be used to scale, rotate, shear and translate the |page| annotations.
DLLEXPORT void STDCALL FPDFPage_TransformAnnots(FPDF_PAGE page,
                                                double a,
                                                double b,
                                                double c,
                                                double d,
                                                double e,
                                                double f);

// Create a new image object.
//
//   document - handle to a document.
//
// Returns a handle to a new image object.
DLLEXPORT FPDF_PAGEOBJECT STDCALL
FPDFPageObj_NewImageObj(FPDF_DOCUMENT document);

// Load an image from a JPEG image file and then set it into |image_object|.
//
//   pages        - pointer to the start of all loaded pages, may be NULL.
//   nCount       - number of |pages|, may be 0.
//   image_object - handle to an image object.
//   fileAccess   - file access handler which specifies the JPEG image file.
//
// Returns TRUE on success.
//
// The image object might already have an associated image, which is shared and
// cached by the loaded pages. In that case, we need to clear the cached image
// for all the loaded pages. Pass |pages| and page count (|nCount|) to this API
// to clear the image cache. If the image is not previously shared, or NULL is a
// valid |pages| value.
DLLEXPORT FPDF_BOOL STDCALL
FPDFImageObj_LoadJpegFile(FPDF_PAGE* pages,
                          int nCount,
                          FPDF_PAGEOBJECT image_object,
                          FPDF_FILEACCESS* fileAccess);

// Load an image from a JPEG image file and then set it into |image_object|.
//
//   pages        - pointer to the start of all loaded pages, may be NULL.
//   nCount       - number of |pages|, may be 0.
//   image_object - handle to an image object.
//   fileAccess   - file access handler which specifies the JPEG image file.
//
// Returns TRUE on success.
//
// The image object might already have an associated image, which is shared and
// cached by the loaded pages. In that case, we need to clear the cached image
// for all the loaded pages. Pass |pages| and page count (|nCount|) to this API
// to clear the image cache. If the image is not previously shared, or NULL is a
// valid |pages| value. This function loads the JPEG image inline, so the image
// content is copied to the file. This allows |fileAccess| and its associated
// data to be deleted after this function returns.
DLLEXPORT FPDF_BOOL STDCALL
FPDFImageObj_LoadJpegFileInline(FPDF_PAGE* pages,
                                int nCount,
                                FPDF_PAGEOBJECT image_object,
                                FPDF_FILEACCESS* fileAccess);

// Set the transform matrix of |image_object|.
//
//   image_object - handle to an image object.
//   a            - matrix value.
//   b            - matrix value.
//   c            - matrix value.
//   d            - matrix value.
//   e            - matrix value.
//   f            - matrix value.
//
// The matrix is composed as:
//   |a c e|
//   |b d f|
// and can be used to scale, rotate, shear and translate the |page| annotations.
//
// Returns TRUE on success.
DLLEXPORT FPDF_BOOL STDCALL FPDFImageObj_SetMatrix(FPDF_PAGEOBJECT image_object,
                                                   double a,
                                                   double b,
                                                   double c,
                                                   double d,
                                                   double e,
                                                   double f);

// Set |bitmap| to |image_object|.
//
//   pages        - pointer to the start of all loaded pages, may be NULL.
//   nCount       - number of |pages|, may be 0.
//   image_object - handle to an image object.
//   bitmap       - handle of the bitmap.
//
// Returns TRUE on success.
DLLEXPORT FPDF_BOOL STDCALL FPDFImageObj_SetBitmap(FPDF_PAGE* pages,
                                                   int nCount,
                                                   FPDF_PAGEOBJECT image_object,
                                                   FPDF_BITMAP bitmap);

// Create a new path object at an initial position.
//
//   x - initial horizontal position.
//   y - initial vertical position.
//
// Returns a handle to a new path object.
DLLEXPORT FPDF_PAGEOBJECT STDCALL FPDFPageObj_CreateNewPath(float x, float y);

// Create a closed path consisting of a rectangle.
//
//   x - horizontal position for the left boundary of the rectangle.
//   y - vertical position for the bottom boundary of the rectangle.
//   w - width of the rectangle.
//   h - height of the rectangle.
//
// Returns a handle to the new path object.
DLLEXPORT FPDF_PAGEOBJECT STDCALL FPDFPageObj_CreateNewRect(float x,
                                                            float y,
                                                            float w,
                                                            float h);

// Get the bounding box of |pageObject|.
//
// pageObject - handle to a page object.
// left       - pointer where the left coordinate will be stored
// bottom     - pointer where the bottom coordinate will be stored
// right      - pointer where the right coordinate will be stored
// top        - pointer where the top coordinate will be stored
//
// Returns TRUE on success.
DLLEXPORT FPDF_BOOL STDCALL FPDFPageObj_GetBounds(FPDF_PAGEOBJECT pageObject,
                                                  float* left,
                                                  float* bottom,
                                                  float* right,
                                                  float* top);

// Set the blend mode of |pageObject|.
//
// pageObject - handle to a page object.
// blend_mode - string containing the blend mode.
//
// Blend mode can be one of following: Color, ColorBurn, ColorDodge, Darken,
// Difference, Exclusion, HardLight, Hue, Lighten, Luminosity, Multiply, Normal,
// Overlay, Saturation, Screen, SoftLight
DLLEXPORT void STDCALL FPDFPageObj_SetBlendMode(FPDF_PAGEOBJECT page,
                                                FPDF_BYTESTRING blend_mode);

// Set the stroke RGBA of a path. Range of values: 0 - 255.
//
// path   - the handle to the path object.
// R      - the red component for the path stroke color.
// G      - the green component for the path stroke color.
// B      - the blue component for the path stroke color.
// A      - the stroke alpha for the path.
//
// Returns TRUE on success.
DLLEXPORT FPDF_BOOL FPDFPath_SetStrokeColor(FPDF_PAGEOBJECT path,
                                            unsigned int R,
                                            unsigned int G,
                                            unsigned int B,
                                            unsigned int A);

// Set the stroke width of a path.
//
// path   - the handle to the path object.
// width  - the width of the stroke.
//
// Returns TRUE on success
DLLEXPORT FPDF_BOOL FPDFPath_SetStrokeWidth(FPDF_PAGEOBJECT path, float width);

// Set the line join of |pageObject|.
//
// pageObject - handle to a page object.
// line_join - line join
//
// Line join can be one of following: FPDF_LINEJOIN_MITER, FPDF_LINEJOIN_ROUND,
// FPDF_LINEJOIN_BEVEL
DLLEXPORT void STDCALL FPDFPath_SetLineJoin(FPDF_PAGEOBJECT page,
                                            int line_join);

// Set the line cap of |pageObject|.
//
// pageObject - handle to a page object.
// line_cap - line cap
//
// Line cap can be one of following: FPDF_LINECAP_BUTT, FPDF_LINECAP_ROUND,
// FPDF_LINECAP_PROJECTING_SQUARE
DLLEXPORT void STDCALL FPDFPath_SetLineCap(FPDF_PAGEOBJECT page, int line_cap);

// Set the fill RGBA of a path. Range of values: 0 - 255.
//
// path   - the handle to the path object.
// R      - the red component for the path fill color.
// G      - the green component for the path fill color.
// B      - the blue component for the path fill color.
// A      - the fill alpha for the path.
//
// Returns TRUE on success.
DLLEXPORT FPDF_BOOL FPDFPath_SetFillColor(FPDF_PAGEOBJECT path,
                                          unsigned int R,
                                          unsigned int G,
                                          unsigned int B,
                                          unsigned int A);

// Get the fill RGBA of a path. Range of values: 0 - 255.
//
// path   - the handle to the path object.
// R      - the red component of the path fill color.
// G      - the green component of the path fill color.
// B      - the blue component of the path fill color.
// A      - the fill alpha of the path.
//
// Returns TRUE on success.
DLLEXPORT FPDF_BOOL FPDFPath_GetFillColor(FPDF_PAGEOBJECT path,
                                          unsigned int* R,
                                          unsigned int* G,
                                          unsigned int* B,
                                          unsigned int* A);

// Move a path's current point.
//
// path   - the handle to the path object.
// x      - the horizontal position of the new current point.
// y      - the vertical position of the new current point.
//
// Note that no line will be created between the previous current point and the
// new one.
//
// Returns TRUE on success
DLLEXPORT FPDF_BOOL FPDFPath_MoveTo(FPDF_PAGEOBJECT path, float x, float y);

// Add a line between the current point and a new point in the path.
//
// path   - the handle to the path object.
// x      - the horizontal position of the new point.
// y      - the vertical position of the new point.
//
// The path's current point is changed to (x, y).
//
// Returns TRUE on success
DLLEXPORT FPDF_BOOL FPDFPath_LineTo(FPDF_PAGEOBJECT path, float x, float y);

// Add a cubic Bezier curve to the given path, starting at the current point.
//
// path   - the handle to the path object.
// x1     - the horizontal position of the first Bezier control point.
// y1     - the vertical position of the first Bezier control point.
// x2     - the horizontal position of the second Bezier control point.
// y2     - the vertical position of the second Bezier control point.
// x3     - the horizontal position of the ending point of the Bezier curve.
// y3     - the vertical position of the ending point of the Bezier curve.
//
// Returns TRUE on success
DLLEXPORT FPDF_BOOL FPDFPath_BezierTo(FPDF_PAGEOBJECT path,
                                      float x1,
                                      float y1,
                                      float x2,
                                      float y2,
                                      float x3,
                                      float y3);

// Close the current subpath of a given path.
//
// path   - the handle to the path object.
//
// This will add a line between the current point and the initial point of the
// subpath, thus terminating the current subpath.
//
// Returns TRUE on success
DLLEXPORT FPDF_BOOL FPDFPath_Close(FPDF_PAGEOBJECT path);

// Set the drawing mode of a path.
//
// path     - the handle to the path object.
// fillmode - the filling mode to be set: 0 for no fill, 1 for alternate, 2 for
// winding.
// stroke   - a boolean specifying if the path should be stroked or not.
//
// Returns TRUE on success
DLLEXPORT FPDF_BOOL FPDFPath_SetDrawMode(FPDF_PAGEOBJECT path,
                                         int fillmode,
                                         FPDF_BOOL stroke);

// Create a new text object using one of the standard PDF fonts.
//
// document   - handle to the document.
// font       - string containing the font name, without spaces.
// font_size  - the font size for the new text object.
//
// Returns a handle to a new text object, or NULL on failure
DLLEXPORT FPDF_PAGEOBJECT STDCALL FPDFPageObj_NewTextObj(FPDF_DOCUMENT document,
                                                         FPDF_BYTESTRING font,
                                                         float font_size);

// Set the text for a textobject. If it had text, it will be replaced.
//
// text_object  - handle to the text object.
// text         - the UTF-16LE encoded string containing the text to be added.
//
// Returns TRUE on success
DLLEXPORT FPDF_BOOL STDCALL FPDFText_SetText(FPDF_PAGEOBJECT text_object,
                                             FPDF_WIDESTRING text);

// Returns a font object loaded from a stream of data. The font is loaded
// into the document.
//
// document   - handle to the document.
// data       - the stream of data, which will be copied by the font object.
// size       - size of the stream, in bytes.
// font_type  - FPDF_FONT_TYPE1 or FPDF_FONT_TRUETYPE depending on the font
// type.
// cid        - a boolean specifying if the font is a CID font or not.
//
// The loaded font can be closed using FPDF_Font_Close.
//
// Returns NULL on failure
DLLEXPORT FPDF_FONT STDCALL FPDFText_LoadFont(FPDF_DOCUMENT document,
                                              const uint8_t* data,
                                              uint32_t size,
                                              int font_type,
                                              FPDF_BOOL cid);

// Set the fill RGBA of a text object. Range of values: 0 - 255.
//
// text_object  - handle to the text object.
// R            - the red component for the path fill color.
// G            - the green component for the path fill color.
// B            - the blue component for the path fill color.
// A            - the fill alpha for the path.
//
// Returns TRUE on success.
DLLEXPORT FPDF_BOOL STDCALL FPDFText_SetFillColor(FPDF_PAGEOBJECT text_object,
                                                  unsigned int R,
                                                  unsigned int G,
                                                  unsigned int B,
                                                  unsigned int A);

// Close a loaded PDF font.
//
// font   - Handle to the loaded font.
DLLEXPORT void STDCALL FPDFFont_Close(FPDF_FONT font);

// Create a new text object using a loaded font.
//
// document   - handle to the document.
// font       - handle to the font object.
// font_size  - the font size for the new text object.
//
// Returns a handle to a new text object, or NULL on failure
DLLEXPORT FPDF_PAGEOBJECT STDCALL
FPDFPageObj_CreateTextObj(FPDF_DOCUMENT document,
                          FPDF_FONT font,
                          float font_size);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  // PUBLIC_FPDF_EDIT_H_
