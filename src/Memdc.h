#ifndef _MEMDC_H_
#define _MEMDC_H_

//////////////////////////////////////////////////
// CMemDC - memory DC
//
class CMemDCEx : public CDC
{
protected:
   CBitmap  m_bitmap;       
   CBitmap* m_oldBitmap;    
   CDC*     m_pDC;          
   CRect    m_rect;         
   BOOL     m_bMemDC;       
    
   void Build( CDC* pDC )
   {
        ASSERT(pDC != NULL); 

        m_pDC		= pDC;
        m_oldBitmap = NULL;
        m_bMemDC	= !pDC->IsPrinting();

        if( m_bMemDC )
		{
            CreateCompatibleDC(pDC);
            pDC->LPtoDP(&m_rect);

            m_bitmap.CreateCompatibleBitmap(pDC, m_rect.Width(), m_rect.Height());
            m_oldBitmap = SelectObject(&m_bitmap);
            
            SetMapMode(pDC->GetMapMode());
            pDC->DPtoLP(&m_rect);
            SetWindowOrg(m_rect.left, m_rect.top);
        }
		else
		{
            m_bPrinting = pDC->m_bPrinting;
            m_hDC       = pDC->m_hDC;
            m_hAttribDC = pDC->m_hAttribDC;
        }

        FillSolidRect( m_rect, pDC->GetBkColor() );
    }

public:
	CMemDCEx( CDC *pDC )
	   : CDC()
   {
	   pDC->GetClipBox( &m_rect );
	   Build( pDC );
   }

	CMemDCEx( HDC hDC )
	   : CDC()
   {
	   CDC::FromHandle( hDC )->GetClipBox( &m_rect );
	   Build( CDC::FromHandle( hDC ) );
   }

	CMemDCEx( CDC *pDC, const RECT& rect )
	   : CDC()
   {
	   m_rect = rect;
	   Build( pDC ); 
   }
    
   virtual ~CMemDCEx()
   {        
        if( m_bMemDC )
		{
            m_pDC->BitBlt( m_rect.left,
				           m_rect.top,
						   m_rect.Width(),
						   m_rect.Height(),
						   this,
						   m_rect.left,
						   m_rect.top,
						   SRCCOPY );            
            
            SelectObject(m_oldBitmap);        
        }
		else
		{
            m_hDC = m_hAttribDC = NULL;
        }    
    }
    
   CMemDCEx* operator->()
    {
        return this;
    }    

    operator CMemDCEx*()
    {
        return this;
    }
};
#endif