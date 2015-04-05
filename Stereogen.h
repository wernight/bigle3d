/** Steregram generator class.
 * Copyright (c) 2005 Werner BEROUX
 * www.beroux.com
 */
#pragma once

#include <FreeImage.h>
#include <FreeImagePlus.h>

class CStereogen
{
// Construction
public:
	CStereogen(void);
	~CStereogen(void);

// Attributes
	void SetPatternImage(const char* szSourceFile);
	void SetReliefImage(const char* szSourceFile);
	void SetDepth(int nDepth);

	// The callback will be called during generation with two arguements: The percents done and the same pParam.
	void SetProcessCallback(void (*callback)(int, void*), void *pParam=NULL);

// Operations
	// Generate the stereogram. Return NULL in case of error.
	FIBITMAP* GenerateStereogram();

	// Return the last error string resource or IDS_NO_ERROR if none.
	UINT GetLastError();

// Implementation
private:
	struct RawImage
	{
		BYTE*	pBits;
		int		nWidth;
		int		nHeight;
		int		nScanWidth;
		int		nBPP;

		BYTE* GetPixel(int x, int y)
		{
			ASSERT(x >= 0 && x < nWidth);
			ASSERT(y >= 0 && y < nHeight);
			return &pBits[y*nScanWidth + x*nBPP/8];
		}

		void SetPixel(int x, int y, BYTE* color)
		{
			ASSERT(x >= 0 && x < nWidth);
			ASSERT(y >= 0 && y < nHeight);
			memcpy(&pBits[y*nScanWidth + x*nBPP/8], color, nBPP/8);
		}

		void BitBlt(int nDestX, int nDestY, int nWidth, int nHeight, RawImage& src, int nSrcX, int nSrcY)
		{
			ASSERT(nBPP == src.nBPP);
			ASSERT(nDestX >= 0 && nDestX+nWidth <= this->nWidth);
			ASSERT(nDestY >= 0 && nDestY+nHeight <= this->nHeight);
			ASSERT(nSrcX >= 0 && nSrcX+nWidth <= src.nWidth);
			ASSERT(nSrcY >= 0 && nSrcY+nHeight <= src.nHeight);

			// For each line
			for (int y=0; y<nHeight; ++y)
				// Copy datas
				memcpy(GetPixel(nDestX, nDestY+y), src.GetPixel(nSrcX, nSrcY+y), nWidth*nBPP/8);
		}
	};

	static FIBITMAP* LoadFile(CString& strFile);
	static bool GetRaw8Bits(FIBITMAP* dibSrc, RawImage* pImage);
	static bool GetRaw24Bits(FIBITMAP* dibSrc, RawImage* pImage);

	// Member variables
	// Generation
	CString		m_strPatternFile,
				m_strReliefFile;
	int			m_nDepth;
	// Callback
	void		(*m_progressCallback)(int, void*);
	void		*m_pProgressCallbackParam;
	// Error
	UINT		m_nLastError;
};
