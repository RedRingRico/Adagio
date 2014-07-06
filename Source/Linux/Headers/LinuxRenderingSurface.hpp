#ifndef __ADAGIO_LINUXRENDERINGSURFACE_HPP__
#define __ADAGIO_LINUXRENDERINGSURFACE_HPP__

#include <RenderingSurface.hpp>

namespace Adagio
{
	class LinuxRenderingSurface : public RenderingSurface
	{
	public:
		LinuxRenderingSurface( );
		~LinuxRenderingSurface( );

		int Initialise( const SURFACE_PROPERTIES &p_SurfaceProperties );

	private:
		LinuxRenderingSurface( const LinuxRenderingSurface &p_Copy );
		operator &LinuxRenderingSurface( const LinuxRenderingSurface &p_Copy );
	};
}

#endif // __ADAGIO_LINUXRENDERINGSURFACE_HPP__

