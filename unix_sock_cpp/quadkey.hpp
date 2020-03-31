//#ifdef _QUADKEY_
#ifndef QUADKEY
#define QUADKEY

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <cstdlib> 
#include <unistd.h>
#include <syscall.h>
#include <iostream> 

using namespace std; 

//namespace tiles
//{
    class TileSystem
    {
    private:
    #define EarthRadius 6378137
    #define MinLatitude -85.05112878
    #define MaxLatitude 85.05112878
    #define MinLongitude -180
    #define MaxLongitude 180

	static double Clip(double n, const double minValue, const double maxValue);
    	static unsigned int MapSize(int levelOfDetail);
        double GroundResolution(double latitude, int levelOfDetail);
  	double MapScale(double latitude, int levelOfDetail, int screenDpi);
    public:

 	void LatLongToPixelXY(double latitude, double longitude, int levelOfDetail, int *pixelX, int *pixelY);
 	static void PixelXYToLatLong(int pixelX, int pixelY, int levelOfDetail, double *latitude, double *longitude);
        static void PixelXYToTileXY(int pixelX, int pixelY, int *tileX, int *tileY);
	static void TileXYToPixelXY(int tileX, int tileY, int *pixelX, int *pixelY);
        static string TileXYToQuadKey(int tileX, int tileY, int levelOfDetail, bool slash);
	static void QuadKeyToTileXY(string quadKey, int *tileX, int *tileY, int *levelOfDetail);
	void do_something();
	int a;
        int b; 
    };

//}
extern "C" {
    extern void quad_update(void *descr, float lat, float lng, int zoom_crit, int zoom_info);
    extern void quad_init();
    extern void quad_clear(void *descr, unsigned short subs, int zoom);
    extern void quad_show();
    extern int  quad_info(int fd);
}
#endif /* QUADKEY */

