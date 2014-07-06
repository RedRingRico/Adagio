#ifndef __ADAGIO_RENDERINGSURFACE_HPP__
#define __ADAGIO_RENDERINGSURFACE_HPP__

namespace Adagio
{
	typedef struct __tagSURFACE_PROPERTIES
	{
		int X;
		int Y;
		int Width;
		int Height;
	}SURFACE_PROPERTIES, *LPSURFACE_PROPERTIES;

	class RenderingSurface
	{
	public:
		virtual ~RenderingSurface( );

		virtual int Initialise(
			const SURFACE_PROPERTIES &p_SurfaceProperties ) = 0;

	protected:
		SURFACE_PROPERTIES	m_SurfaceProperties;
	};
}

#endif // __ADAGIO_RENDERINGSURFACE_HPP__

