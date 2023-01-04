#pragma once
#include "FastLED.h"

/* FastLED_RGBW
 * 
 * Hack to enable SK6812 RGBW strips to work with FastLED.
 *
 * Original code by Jim Bumgardner (http://krazydad.com).
 * Modified by David Madison (http://partsnotincluded.com).
 * 
*/
#ifndef FastLED_RGBW_h
#define FastLED_RGBW_h
struct CRGBW  {
	union {
		struct {
			union {
				uint8_t g;
				uint8_t green;
			};
			union {
				uint8_t r;
				uint8_t red;
			};
			union {
				uint8_t b;
				uint8_t blue;
			};
			union {
				uint8_t w;
				uint8_t white;
			};
		};
		uint8_t raw[4];
	};
	CRGBW(){}
	CRGBW(uint8_t rd, uint8_t grn, uint8_t blu, uint8_t wht){
		r = rd;
		g = grn;
		b = blu;
		w = wht;
	}
	inline void operator = (const CRGB c) __attribute__((always_inline)){ 
		this->r = c.r;
		this->g = c.g;
		this->b = c.b;
		this->white = 0;
	}

    /// allow assignment from one RGB struct to another
	inline CRGBW& operator= (const CRGBW& rhs) __attribute__((always_inline)) = default;

    /// allow assignment from 32-bit (really 24-bit) 0xRRGGBB color code
	inline CRGBW& operator= (const uint32_t colorcode) __attribute__((always_inline))
    {
        r = (colorcode >> 16) & 0xFF;
        g = (colorcode >>  8) & 0xFF;
        b = (colorcode >>  0) & 0xFF;
        return *this;
    }

    /// allow assignment from R, G, and B
	inline CRGBW& setRGB (uint8_t nr, uint8_t ng, uint8_t nb) __attribute__((always_inline))
    {
        r = nr;
        g = ng;
        b = nb;
        return *this;
    }

    /// allow assignment from 32-bit (really 24-bit) 0xRRGGBB color code
	inline CRGBW& setColorCode (uint32_t colorcode) __attribute__((always_inline))
    {
        r = (colorcode >> 16) & 0xFF;
        g = (colorcode >>  8) & 0xFF;
        b = (colorcode >>  0) & 0xFF;
        return *this;
    }


    /// add one RGB to another, saturating at 0xFF for each channel
    inline CRGBW& operator+= (const CRGBW& rhs )
    {
        r = qadd8( r, rhs.r);
        g = qadd8( g, rhs.g);
        b = qadd8( b, rhs.b);
        w = qadd8( w, rhs.w);
        return *this;
    }

    /// add a contstant to each channel, saturating at 0xFF
    /// this is NOT an operator+= overload because the compiler
    /// can't usefully decide when it's being passed a 32-bit
    /// constant (e.g. CRGBW::Red) and an 8-bit one (CRGBW::Blue)
    inline CRGBW& addToRGB (uint8_t d )
    {
        r = qadd8( r, d);
        g = qadd8( g, d);
        b = qadd8( b, d);
        w = qadd8( w, d);
        return *this;
    }

    /// subtract one RGB from another, saturating at 0x00 for each channel
    inline CRGBW& operator-= (const CRGBW& rhs )
    {
        r = qsub8( r, rhs.r);
        g = qsub8( g, rhs.g);
        b = qsub8( b, rhs.b);
        w = qsub8( w, rhs.w);
        return *this;
    }

    /// subtract a constant from each channel, saturating at 0x00
    /// this is NOT an operator+= overload because the compiler
    /// can't usefully decide when it's being passed a 32-bit
    /// constant (e.g. CRGBW::Red) and an 8-bit one (CRGBW::Blue)
    inline CRGBW& subtractFromRGB(uint8_t d )
    {
        r = qsub8( r, d);
        g = qsub8( g, d);
        b = qsub8( b, d);
        w = qsub8( w, d);
        return *this;
    }

    /// subtract a constant of '1' from each channel, saturating at 0x00
    inline CRGBW& operator-- ()  __attribute__((always_inline))
    {
        subtractFromRGB(1);
        return *this;
    }

    /// subtract a constant of '1' from each channel, saturating at 0x00
    inline CRGBW operator-- (int )  __attribute__((always_inline))
    {
        CRGBW retval(*this);
        --(*this);
        return retval;
    }

    /// add a constant of '1' from each channel, saturating at 0xFF
    inline CRGBW& operator++ ()  __attribute__((always_inline))
    {
        addToRGB(1);
        return *this;
    }

    /// add a constant of '1' from each channel, saturating at 0xFF
    inline CRGBW operator++ (int )  __attribute__((always_inline))
    {
        CRGBW retval(*this);
        ++(*this);
        return retval;
    }

    /// divide each of the channels by a constant
    inline CRGBW& operator/= (uint8_t d )
    {
        r /= d;
        g /= d;
        b /= d;
        w /= d;
        return *this;
    }

    /// right shift each of the channels by a constant
    inline CRGBW& operator>>= (uint8_t d)
    {
        r >>= d;
        g >>= d;
        b >>= d;
        w >>= d;
        return *this;
    }

    /// multiply each of the channels by a constant,
    /// saturating each channel at 0xFF
    inline CRGBW& operator*= (uint8_t d )
    {
        r = qmul8( r, d);
        g = qmul8( g, d);
        b = qmul8( b, d);
        w = qmul8( w, d);
        return *this;
    }

    /// scale down a RGB to N 256ths of it's current brightness, using
    /// 'video' dimming rules, which means that unless the scale factor is ZERO
    /// each channel is guaranteed NOT to dim down to zero.  If it's already
    /// nonzero, it'll stay nonzero, even if that means the hue shifts a little
    /// at low brightness levels.
    inline CRGBW& nscale8_video (uint8_t scaledown )
    {
        nscale8x2_video( r, g, scaledown);
        nscale8x2_video( b, w, scaledown);
        return *this;
    }

    /// %= is a synonym for nscale8_video.  Think of it is scaling down
    /// by "a percentage"
    inline CRGBW& operator%= (uint8_t scaledown )
    {
        nscale8x2_video( r, g, scaledown);
        nscale8x2_video( b, w, scaledown);
        return *this;
    }

    /// fadeLightBy is a synonym for nscale8_video( ..., 255-fadefactor)
    inline CRGBW& fadeLightBy (uint8_t fadefactor )
    {
        nscale8x2_video( r, g, 255 - fadefactor);
        nscale8x2_video( b, w, 255 - fadefactor);
        return *this;
    }

    /// scale down a RGB to N 256ths of it's current brightness, using
    /// 'plain math' dimming rules, which means that if the low light levels
    /// may dim all the way to 100% black.
    inline CRGBW& nscale8 (uint8_t scaledown )
    {
        nscale8x2( r, g, scaledown);
        nscale8x2( b, w, scaledown);
        return *this;
    }

    /// scale down a RGB to N 256ths of it's current brightness, using
    /// 'plain math' dimming rules, which means that if the low light levels
    /// may dim all the way to 100% black.
    inline CRGBW& nscale8 (const CRGBW & scaledown )
    {
        r = ::scale8(r, scaledown.r);
        g = ::scale8(g, scaledown.g);
        b = ::scale8(b, scaledown.b);
        w = ::scale8(w, scaledown.w);
        return *this;
    }

    /// return a CRGBW object that is a scaled down version of this object
    inline CRGBW scale8 (uint8_t scaledown ) const
    {
        CRGBW out = *this;
        nscale8x2( out.r, out.g, scaledown);
        nscale8x2( out.b, out.w, scaledown);
        return out;
    }

    /// return a CRGBW object that is a scaled down version of this object
    inline CRGBW scale8 (const CRGBW & scaledown ) const
    {
        CRGBW out;
        out.r = ::scale8(r, scaledown.r);
        out.g = ::scale8(g, scaledown.g);
        out.b = ::scale8(b, scaledown.b);
        out.w = ::scale8(w, scaledown.w);
        return out;
    }

    /// fadeToBlackBy is a synonym for nscale8( ..., 255-fadefactor)
    inline CRGBW& fadeToBlackBy (uint8_t fadefactor )
    {
        nscale8x2( r, g, 255 - fadefactor);
        nscale8x2( b, w, 255 - fadefactor);
        return *this;
    }

    /// "or" operator brings each channel up to the higher of the two values
    inline CRGBW& operator|= (const CRGBW& rhs )
    {
        if( rhs.r > r) r = rhs.r;
        if( rhs.g > g) g = rhs.g;
        if( rhs.b > b) b = rhs.b;
        if( rhs.w > w) w = rhs.w;
        return *this;
    }

    /// "or" operator brings each channel up to the higher of the two values
    inline CRGBW& operator|= (uint8_t d )
    {
        if( d > r) r = d;
        if( d > g) g = d;
        if( d > b) b = d;
        if( d > w) w = d;
        return *this;
    }

    /// "and" operator brings each channel down to the lower of the two values
    inline CRGBW& operator&= (const CRGBW& rhs )
    {
        if( rhs.r < r) r = rhs.r;
        if( rhs.g < g) g = rhs.g;
        if( rhs.b < b) b = rhs.b;
        if( rhs.w < w) w = rhs.w;
        return *this;
    }

    /// "and" operator brings each channel down to the lower of the two values
    inline CRGBW& operator&= (uint8_t d )
    {
        if( d < r) r = d;
        if( d < g) g = d;
        if( d < b) b = d;
        if( d < w) w = d;
        return *this;
    }

    /// this allows testing a CRGBW for zero-ness
    inline operator bool() const __attribute__((always_inline))
    {
        return r || g || b || w;
    }

    /// invert each channel
    inline CRGBW operator- () const
    {
        CRGBW retval;
        retval.r = 255 - r;
        retval.g = 255 - g;
        retval.b = 255 - b;
        retval.w = 255 - w;
        return retval;
    }

    /// Get the 'luma' of a CRGBW object - aka roughly how much light the
    /// CRGBW pixel is putting out (from 0 to 255).
    inline uint8_t getLuma ( )  const {
        //Y' = 0.2126 R' + 0.7152 G' + 0.0722 B'
        //     54            183       18 (!)

        uint8_t luma = scale8_LEAVING_R1_DIRTY( r, 27) + \
        scale8_LEAVING_R1_DIRTY( g, 92) + \
        scale8_LEAVING_R1_DIRTY( b, 9) + \
        scale8_LEAVING_R1_DIRTY( w, 128);
        cleanup_R1();
        return luma;
    }

    /// Get the average of the R, G, and B values
    inline uint8_t getAverageLight( )  const {
        uint8_t avg = scale8_LEAVING_R1_DIRTY( r, 64) + \
        scale8_LEAVING_R1_DIRTY( g, 64) + \
        scale8_LEAVING_R1_DIRTY( b, 64) + \
        scale8_LEAVING_R1_DIRTY( w, 64)
        ;
        cleanup_R1();
        return avg;
    }

    /// maximize the brightness of this CRGBW object
    inline void maximizeBrightness( uint8_t limit = 255 )  {
        uint8_t max = red;
        if( green > max) max = green;
        if( blue > max) max = blue;

        // stop div/0 when color is black
        if(max > 0) {
            uint16_t factor = ((uint16_t)(limit) * 256) / max;
            red =   (red   * factor) / 256;
            green = (green * factor) / 256;
            blue =  (blue  * factor) / 256;
        }
    }

    /// return a new CRGBW object after performing a linear interpolation between this object and the passed in object
    inline CRGBW lerp8( const CRGBW& other, fract8 frac) const
    {
        CRGBW ret;

        ret.r = lerp8by8(r,other.r,frac);
        ret.g = lerp8by8(g,other.g,frac);
        ret.b = lerp8by8(b,other.b,frac);
        ret.w = lerp8by8(w,other.w,frac);

        return ret;
    }

    /// return a new CRGBW object after performing a linear interpolation between this object and the passed in object
    inline CRGBW lerp16( const CRGBW& other, fract16 frac) const
    {
        CRGBW ret;

        ret.r = lerp16by16(r<<8,other.r<<8,frac)>>8;
        ret.g = lerp16by16(g<<8,other.g<<8,frac)>>8;
        ret.b = lerp16by16(b<<8,other.b<<8,frac)>>8;
        ret.w = lerp16by16(w<<8,other.w<<8,frac)>>8;

        return ret;
    }
};
inline uint16_t getRGBWsize(uint16_t nleds){
	uint16_t nbytes = nleds * 4;
	if(nbytes % 3 > 0) return nbytes / 3 + 1;
	else return nbytes / 3;
}
#endif

#include "ArduinoJson.h"

namespace ARDUINOJSON_NAMESPACE {
template <>
struct Converter<CRGB> {
  static void toJson(const CRGB& src, VariantRef dst) {
    dst["r"] = src.r;
    dst["g"] = src.g;
    dst["b"] = src.b;
  }

  static CRGB fromJson(VariantConstRef src) {
    return CRGB(src["r"], src["g"], src["b"]);
  }

  static bool checkJson(VariantConstRef src) {
    return src["r"].is<uint8_t>() && src["g"].is<uint8_t>() && src["b"].is<uint8_t>();
  }
};
}

namespace ARDUINOJSON_NAMESPACE {
template <>
struct Converter<CHSV> {
  static bool toJson(const CHSV& src, VariantRef dst) {
    dst["h"] = src.h;
    dst["s"] = src.s;
    dst["v"] = src.v;
    return true;
  }

  static CHSV fromJson(VariantConstRef src) {
    return CHSV(src["h"], src["s"], src["v"]);
  }

  static bool checkJson(VariantConstRef src) {
    return src["h"].is<uint8_t>() && src["s"].is<uint8_t>() && src["v"].is<uint8_t>();
  }
};
}

