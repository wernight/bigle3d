#include "StdAfx.h"
#include "Stereogen.h"
#include "Resource.h"

CStereogen::CStereogen(void) :
	m_nDepth(30),
	m_nLastError(IDS_NO_ERROR)
{
	m_progressCallback = NULL;
}

CStereogen::~CStereogen(void)
{
}

void CStereogen::SetPatternImage(const char* szSourceFile)
{
	m_strPatternFile = szSourceFile;
}

void CStereogen::SetReliefImage(const char* szSourceFile)
{
	m_strReliefFile = szSourceFile;
}

void CStereogen::SetDepth(int nDepth)
{
	m_nDepth = nDepth;
}

void CStereogen::SetProcessCallback(void (*callback)(int, void*), void *pParam/*=NULL*/)
{
	m_progressCallback = callback;
	m_pProgressCallbackParam = pParam;
}

FIBITMAP* CStereogen::GenerateStereogram()
{
	FIBITMAP	*src = NULL,
				*fiStereogram = NULL;
	RawImage	imgStrip,
				imgRelief,
				imgStereogram;
	int			i,
				xShift,
				xStrip,
				nMin,
				nMax;
	register int x, y;

	try
	{
		imgStrip.pBits = NULL;
		imgRelief.pBits = NULL;
		imgStereogram.pBits = NULL;

		// Load pattern
		if ((src = LoadFile( m_strPatternFile )) == NULL ||
			!GetRaw24Bits(src, &imgStrip))
			throw IDS_PATTERN_LOAD_ERROR;
		FreeImage_Unload(src);
		src = NULL;

		// Load relief
		if ((src = LoadFile( m_strReliefFile )) == NULL ||
			!GetRaw8Bits(src, &imgRelief))
			throw IDS_RELIEF_LOAD_ERROR;
		FreeImage_Unload(src);
		src = NULL;

		// Allocate final stereogram image
		src = FreeImage_Allocate(
			imgRelief.nWidth + imgStrip.nWidth,
			imgRelief.nHeight,
			24,
			FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK);
		if (src == NULL)
			throw IDS_FINAL_ALLOCATE_ERROR;
		if (!GetRaw24Bits(src, &imgStereogram))
			throw IDS_FINAL_ALLOCATE_ERROR;
		FreeImage_Unload(src);
		src = NULL;

		// Generate strip by strip (middle -> right)
		nMin = imgRelief.nWidth/2;
		nMax = imgRelief.nWidth + imgStrip.nWidth;
		for (i=nMin; i<nMax; i+=imgStrip.nWidth)
		{
			// Display progression
			if (m_progressCallback != NULL)
				m_progressCallback((i-nMin)*100/nMax, m_pProgressCallbackParam);

			// Generate next vertical strip
			for (x=0; x<imgStrip.nWidth && x+i<nMax; x++)
				for (y=0; y<imgRelief.nHeight; y++)
				{
					xShift = *imgRelief.GetPixel(i-imgStrip.nWidth+x, y) * m_nDepth / 0xFF;
					if (xShift != 0)
					{
						xStrip = x + xShift;
						if (xStrip >= imgStrip.nWidth)
							xStrip -= imgStrip.nWidth;
						imgStrip.SetPixel(x, y, imgStrip.GetPixel(xStrip, y));
					}
				}

			// Copy to final image
			if (i+imgStrip.nWidth > imgStereogram.nWidth)
				imgStereogram.BitBlt(
					i, 0,	// x, y in dest
					imgStereogram.nWidth-i, imgRelief.nHeight,		// width, height to copy
					imgStrip,	// source
					0, 0);	// x, y in source
			else
				imgStereogram.BitBlt(
					i, 0,	// x, y in dest
					imgStrip.nWidth, imgRelief.nHeight,		// width, height to copy
					imgStrip,	// source
					0, 0);	// x, y in source
		}

		// Strip := Middle strip := Original pattern
		imgStrip.BitBlt(
			0, 0,	// x, y in dest
			imgStrip.nWidth, imgRelief.nHeight,		// width, height to copy
			imgStereogram,	// source
			imgRelief.nWidth/2, 0);	// x, y in source

		// Generate strip by strip (middle -> left)
		nMax = imgRelief.nWidth/2 - imgStrip.nWidth;
		for (i=nMax; i+imgStrip.nWidth>=0; i-=imgStrip.nWidth)
		{
			// Display progression
			if (m_progressCallback != NULL)
			{
				if (nMax == 0)
					m_progressCallback(100, m_pProgressCallbackParam);
				else
					m_progressCallback(100 - i * ((nMax+imgStrip.nWidth)*100/(imgRelief.nWidth+imgStrip.nWidth)) / nMax, m_pProgressCallbackParam);
			}

			// Generate next vertical strip
			for (x=imgStrip.nWidth-1; x>=0 && x+i>=0; x--)
				for (y=0; y<imgRelief.nHeight; y++)
				{
					xShift = *imgRelief.GetPixel(i+x, y) * m_nDepth / 255;
					if (xShift != 0)
					{
						xStrip = x - xShift;
						if (xStrip < 0)
							xStrip += imgStrip.nWidth;
						imgStrip.SetPixel(x, y, imgStrip.GetPixel(xStrip, y));
					}
				}

			// Copy to final DC
			if (i < 0)
                imgStereogram.BitBlt(0, 0, imgStrip.nWidth-abs(i), imgRelief.nHeight, imgStrip, abs(i), 0);
			else
				imgStereogram.BitBlt(i, 0, imgStrip.nWidth, imgRelief.nHeight, imgStrip, 0, 0);
		}

		// Convert to FIBITMAP
		fiStereogram = FreeImage_ConvertFromRawBits(
			imgStereogram.pBits,
			imgStereogram.nWidth,
			imgStereogram.nHeight,
			imgStereogram.nScanWidth,
			imgStereogram.nBPP,
	        FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, TRUE);
		if (fiStereogram == NULL)
			throw IDS_FINAL_ALLOCATE_ERROR;

		// Display progression
		if (m_progressCallback != NULL)
			m_progressCallback(100, m_pProgressCallbackParam);
	}
	catch (UINT nErrorString)
	{
		m_nLastError = nErrorString;
	}
	catch (...)
	{
		m_nLastError = IDS_GENERIC_ERROR;
	}

	// Clean up
	if (imgStrip.pBits != NULL)
		delete [] imgStrip.pBits;
	if (imgRelief.pBits != NULL)
		delete [] imgRelief.pBits;
	if (imgStereogram.pBits != NULL)
		delete [] imgStereogram.pBits;
	if (src != NULL)
		FreeImage_Unload(src);

	return fiStereogram;
}

UINT CStereogen::GetLastError()
{
	return m_nLastError;
}

FIBITMAP* CStereogen::LoadFile(CString& strFile)
{
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;

	// check the file signature and deduce its format
	// (the second argument is currently not used by FreeImage)
	fif = FreeImage_GetFileType(strFile, 0);
	if (fif == FIF_UNKNOWN)
	{
		// no signature ?
		// try to guess the file format from the file extension
		fif = FreeImage_GetFIFFromFilename(strFile);
	}

	// check that the plugin has reading capabilities ...
	if ((fif != FIF_UNKNOWN) && FreeImage_FIFSupportsReading(fif))
	{
		// ok, let's load the file
		FIBITMAP *dib = FreeImage_Load(fif, strFile, 0);

		// unless a bad file format, we are done !
		return dib;
	}
	return NULL;
}

bool CStereogen::GetRaw8Bits(FIBITMAP* dibSrc, RawImage* pImage)
{
	ASSERT(dibSrc != NULL);
	ASSERT(pImage != NULL);

	// Convert to gray scale
	FIBITMAP *src = FreeImage_ConvertToStandardType(dibSrc);
	if (src == NULL)
		return false;

    // Allocate a raw buffer
	pImage->nWidth = FreeImage_GetWidth(src);
    pImage->nHeight = FreeImage_GetHeight(src);
    pImage->nScanWidth = FreeImage_GetPitch(src);
    pImage->pBits = new BYTE[pImage->nHeight * pImage->nScanWidth];
	pImage->nBPP = 8;
	if (pImage->pBits == NULL)
	{
		FreeImage_Unload(src);
		return false;
	}
    
	// Convert the bitmap to raw bits (top-left pixel first)
	FreeImage_ConvertToRawBits(pImage->pBits, src, pImage->nScanWidth, 8,
        FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, TRUE);
	FreeImage_Unload(src);
	return true;
}

bool CStereogen::GetRaw24Bits(FIBITMAP* dibSrc, RawImage* pImage)
{
	ASSERT(dibSrc != NULL);
	ASSERT(pImage != NULL);

	// Convert to 24 bits
	FIBITMAP *src = FreeImage_ConvertTo24Bits(dibSrc);
	if (src == NULL)
		return false;

    // Allocate a raw buffer
	pImage->nWidth = FreeImage_GetWidth(src);
    pImage->nHeight = FreeImage_GetHeight(src);
    pImage->nScanWidth = FreeImage_GetPitch(src);
    pImage->pBits = new BYTE[pImage->nHeight * pImage->nScanWidth];
	pImage->nBPP = 24;
	if (pImage->pBits == NULL)
	{
		FreeImage_Unload(src);
		return false;
	}
    
	// Convert the bitmap to raw bits (top-left pixel first)
	FreeImage_ConvertToRawBits(pImage->pBits, src, pImage->nScanWidth, 24,
        FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, TRUE);
	FreeImage_Unload(src);
	return true;
}
