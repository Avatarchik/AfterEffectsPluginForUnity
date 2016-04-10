#include "pch.h"
#include "aepInternal.h"


template<class T> struct aepPixelTraits;
template<> struct aepPixelTraits<PF_Pixel>
{
    typedef A_u_char elem_t;
    typedef PF_IteratePixel8Func iter_t;
    typedef PF_BatchSampleFunc batch_t;

};
template<> struct aepPixelTraits<PF_Pixel16>
{
    typedef A_u_short elem_t;
    typedef PF_IteratePixel16Func iter_t;
    typedef PF_BatchSample16Func batch_t;
};
template<> struct aepPixelTraits<PF_PixelFloat>
{
    typedef PF_FpShort elem_t;
    typedef PF_IteratePixelFloatFunc iter_t;
};


////////////////////////////////////////////////////////////////
// host callbacks
////////////////////////////////////////////////////////////////

static PF_Err pf_checkout_param(
    PF_ProgPtr		effect_ref,	/* reference from in_data */
    PF_ParamIndex	index, 		/* 0 = input, 1..n = param */
    A_long			what_time,
    A_long			time_step,	/* duration between frames in time_scale units */
    A_u_long	time_scale,
    PF_ParamDef		*param)	/* the param you've been waiting for...	*/
{
    auto ins = (aepInstance*)effect_ref;
    aepTrace("instance: %p", ins);
    return PF_Err_NONE;
}

static PF_Err pf_checkin_param(
    PF_ProgPtr		effect_ref,	/* reference from in_data */
    PF_ParamDef		*param)
{
    auto ins = (aepInstance*)effect_ref;
    aepTrace("instance: %p", ins);
    return PF_Err_NONE;
}

static PF_Err pf_add_param(
    PF_ProgPtr		effect_ref,	/* reference from in_data */
    PF_ParamIndex	index,		/* -1 = add to end */
    PF_ParamDefPtr	def)
{
    auto ins = (aepInstance*)effect_ref;
    aepTrace("instance: %p", ins);
    ins->addParam(index, *def);
    return PF_Err_NONE;
}

static PF_Err pf_abort(
    PF_ProgPtr		effect_ref)	/* reference from in_data */
{
    auto ins = (aepInstance*)effect_ref;
    aepTrace("instance: %p", ins);
    return PF_Err_NONE;
}

static PF_Err pf_progress(
    PF_ProgPtr		effect_ref,	/* reference from in_data */
    A_long			current,
    A_long			total)
{
    auto ins = (aepInstance*)effect_ref;
    aepTrace("instance: %p", ins);
    return PF_Err_NONE;
}

static PF_Err pf_register_ui(
    PF_ProgPtr			effect_ref,	/* reference from in_data	*/
    PF_CustomUIInfo		*cust_info)
{
    auto ins = (aepInstance*)effect_ref;
    aepTrace("instance: %p", ins);
    return PF_Err_NONE;
}

static PF_Err pf_checkout_layer_audio(
    PF_ProgPtr		effect_ref,	/* reference from in_data */
    PF_ParamIndex	index, 		/* 0 = input, 1..n = param */
    A_long			start_time,	/* in time_scale units */
    A_long			duration,	/* in time_scale units */
    A_u_long	time_scale,	/* units/sec */
    PF_UFixed		rate,		/* unsigned! */
    A_long			bytes_per_sample,
    A_long			num_channels,
    A_long			fmt_signed,	/* non-zero for signed, zero for unsigned */
    PF_LayerAudio	*audio)	/* the LayerAudio you've been waiting for...	*/
{
    auto ins = (aepInstance*)effect_ref;
    aepTrace("instance: %p", ins);
    return PF_Err_NONE;
}

static PF_Err pf_checkin_layer_audio(
    PF_ProgPtr		effect_ref,	/* reference from in_data */
    PF_LayerAudio	audio)
{
    auto ins = (aepInstance*)effect_ref;
    aepTrace("instance: %p", ins);
    return PF_Err_NONE;
}

static PF_Err pf_get_audio_data(
    PF_ProgPtr		effect_ref,			/* reference from in_data */
    PF_LayerAudio	audio,
    PF_SndSamplePtr	*data0,				/* optional - packed array of samples, if stereo, left/right */
    A_long			*num_samples0,		/* optional */
    PF_UFixed		*rate0,				/* optional - unsigned! */
    A_long			*bytes_per_sample0,	/* optional */
    A_long			*num_channels0,		/* optional */
    A_long			*fmt_signed0)		/* optional - non-zero for signed, zero for unsigned */
{
    auto ins = (aepInstance*)effect_ref;
    aepTrace("instance: %p", ins);
    return PF_Err_NONE;
}


////////////////////////////////////////////////////////////////
// utility callbacks
////////////////////////////////////////////////////////////////

static PF_Err pf_gaussian_kernel(
    PF_ProgPtr		effect_ref,		/* reference from in_data */
    A_FpLong			kRadius,		/* desired gaussian radius */
    PF_KernelFlags	flags,			/* see kernel flags commented above */
    A_FpLong			multiplier,
    A_long			*diameter,
    void			*kernel)
{
    auto ins = (aepInstance*)effect_ref;
    aepTrace("instance: %p", ins);
    return PF_Err_NONE;
}

static PF_Err pf_get_callback_addr(
    PF_ProgPtr		effect_ref,		/* reference from in_data */
    PF_Quality		quality,
    PF_ModeFlags	mode_flags,
    PF_CallbackID	which_callback,
    PF_CallbackFunc	*fn_ptr)
{
    auto ins = (aepInstance*)effect_ref;
    aepTrace("instance: %p", ins);
    return PF_Err_NONE;
}

static PF_Err pf_app(PF_ProgPtr effect_ref, A_long, ...)	/* application specific callback */
{
    auto ins = (aepInstance*)effect_ref;
    aepTrace("instance: %p", ins);
    return PF_Err_NONE;
}

static PF_Err pf_get_platform_data(
    PF_ProgPtr		effect_ref,
    PF_PlatDataID	which,
    void			*data)
{
    auto ins = (aepInstance*)effect_ref;
    aepTrace("instance: %p", ins);
    return PF_Err_NONE;
}


////////////////////////////////////////////////////////////////
// PF Handle Suite
////////////////////////////////////////////////////////////////

static PF_Handle pf_host_new_handle(A_u_longlong size)
{
    aepTrace("size: %u", (uint32_t)size);
    return nullptr;
}

static void* pf_host_lock_handle(PF_Handle pf_handle)
{
    aepTrace("pf_handle: %p", pf_handle);
    return nullptr;
}

static void pf_host_unlock_handle(PF_Handle pf_handle)
{
    aepTrace("pf_handle: %p", pf_handle);
}

static void pf_host_dispose_handle(PF_Handle pf_handle)
{
    aepTrace("pf_handle: %p", pf_handle);
}

static A_u_longlong pf_host_get_handle_size(PF_Handle pf_handle)
{
    aepTrace("pf_handle: %p", pf_handle);
    return 0;
}
static PF_Err pf_host_resize_handle(
    A_u_longlong		new_sizeL,		/* >> */
    PF_Handle			*handlePH)		/* <> Handle Value May Change */
{
    aepTrace("new_sizeL: %u", (uint32_t)new_sizeL);
    return PF_Err_NONE;
}


////////////////////////////////////////////////////////////////
// PF ANSI Suite
////////////////////////////////////////////////////////////////

static A_FpLong pf_atan(A_FpLong a) { aepTrace2(); return atan(a); }
static A_FpLong pf_atan2(A_FpLong y, A_FpLong x) { aepTrace2(); return atan2(y, x); }
static A_FpLong pf_ceil(A_FpLong a) { aepTrace2(); return ceil(a); }
static A_FpLong pf_cos(A_FpLong a) { aepTrace2(); return cos(a); }
static A_FpLong pf_exp(A_FpLong a) { aepTrace2(); return exp(a); }
static A_FpLong pf_fabs(A_FpLong a) { aepTrace2(); return fabs(a); }
static A_FpLong pf_floor(A_FpLong a) { aepTrace2(); return floor(a); }
static A_FpLong pf_fmod(A_FpLong x, A_FpLong y) { aepTrace2(); return fmod(x, y); }
static A_FpLong pf_hypot(A_FpLong x, A_FpLong y) { aepTrace2(); return hypot(x, y); }
static A_FpLong pf_log(A_FpLong a) { aepTrace2(); return log(a); }
static A_FpLong pf_log10(A_FpLong a) { aepTrace2(); return log10(a); }
static A_FpLong pf_pow(A_FpLong x, A_FpLong y) { aepTrace2(); return pow(x, y); }
static A_FpLong pf_sin(A_FpLong a) { aepTrace2(); return sin(a); }
static A_FpLong pf_sqrt(A_FpLong a) { aepTrace2(); return sqrt(a); }
static A_FpLong pf_tan(A_FpLong a) { aepTrace2(); return tan(a); }
static int pf_sprintf(A_char *buf, const A_char *fmt, ...)
{
    aepTrace2();
    va_list vl;
    va_start(vl, fmt);
    int ret = vsprintf(buf, fmt, vl);
    va_end(vl);
    return ret;
}
static A_char* pf_strcpy(A_char *a, const A_char *b) { aepTrace2(); return strcpy(a, b); }
static A_FpLong pf_asin(A_FpLong a) { aepTrace2(); return asin(a); }
static A_FpLong pf_acos(A_FpLong a) { aepTrace2(); return acos(a); }


////////////////////////////////////////////////////////////////
// PF Pixel Data Suite
////////////////////////////////////////////////////////////////

template<class C>
static PF_Err pf_get_pixel_data(
    PF_EffectWorld	*worldP,
    PF_PixelPtr		pixelsP0,		// NULL to use data in PF_EffectWorld
    C		**pixPP)		// will return NULL if depth mismatch
{
    aepTrace2();
    return PF_Err_NONE;
}


////////////////////////////////////////////////////////////////
// PF Color Suite
////////////////////////////////////////////////////////////////

// PF_Pixel, PF_Pixel16, PF_PixelFloat
template<class C>
static PF_Err pf_RGBtoHLS(PF_ProgPtr effect_ref, C *rgb, PF_HLS_Pixel hls)
{
    aepTrace2();
    return PF_Err_NONE;
}

template<class C>
static PF_Err pf_HLStoRGB(PF_ProgPtr effect_ref, PF_HLS_Pixel hls, C *rgb)
{
    aepTrace2();
    return PF_Err_NONE;
}

template<class C>
static PF_Err pf_RGBtoYIQ(PF_ProgPtr effect_ref, C *rgb, PF_YIQ_Pixel yiq)
{
    aepTrace2();
    return PF_Err_NONE;
}

template<class C>
static PF_Err pf_YIQtoRGB(PF_ProgPtr effect_ref, PF_YIQ_Pixel yiq, C *rgb)
{
    aepTrace2();
    return PF_Err_NONE;
}

template<class C>
static PF_Err pf_Luminance(PF_ProgPtr effect_ref, C *rgb, A_long *lum100)
{
    aepTrace2();
    return PF_Err_NONE;
}

template<class C>
static PF_Err pf_Hue(PF_ProgPtr effect_ref, C *rgb, A_long *hue)
{
    aepTrace2();
    return PF_Err_NONE;
}

template<class C>
static PF_Err pf_Lightness(PF_ProgPtr effect_ref, C *rgb, A_long *lightness)
{
    aepTrace2();
    return PF_Err_NONE;
}

template<class C>
static PF_Err pf_Saturation(PF_ProgPtr effect_ref, C *rgb, A_long *saturation)
{
    aepTrace2();
    return PF_Err_NONE;
}


////////////////////////////////////////////////////////////////
// PF Batch Sampling Suite
////////////////////////////////////////////////////////////////

static PF_Err pf_begin_sampling(
    PF_ProgPtr		effect_ref,		/* reference from in_data */
    PF_Quality		qual,
    PF_ModeFlags	mf,
    PF_SampPB		*params)
{
    aepTrace2();
    return PF_Err_NONE;
}

static PF_Err pf_end_sampling(
    PF_ProgPtr		effect_ref,		/* reference from in_data */
    PF_Quality		qual,
    PF_ModeFlags	mf,
    PF_SampPB		*params)
{
    aepTrace2();
    return PF_Err_NONE;
}

template<class C>
static PF_Err pf_get_batch_func(
    PF_ProgPtr			effect_ref,		/* reference from in_data */
    PF_Quality			quality,
    PF_ModeFlags		mode_flags,
    const PF_SampPB		*params,
    typename aepPixelTraits<C>::batch_t	*batch)
{
    aepTrace2();
    return PF_Err_NONE;
}


////////////////////////////////////////////////////////////////
// PF Sampling Suite
////////////////////////////////////////////////////////////////

template<class C>
static PF_Err pf_nn_sample(
    PF_ProgPtr		effect_ref,		/* reference from in_data */
    PF_Fixed		x,
    PF_Fixed		y,
    const PF_SampPB	*params,
    C		*dst_pixel)
{
    aepTrace2();
    auto ins = (aepInstance*)effect_ref;
    return PF_Err_NONE;
}

template<class C>
static PF_Err pf_subpixel_sample(
    PF_ProgPtr		effect_ref,		/* reference from in_data */
    PF_Fixed		x,
    PF_Fixed		y,
    const PF_SampPB	*params,
    C		*dst_pixel)
{
    aepTrace2();
    auto ins = (aepInstance*)effect_ref;
    return PF_Err_NONE;
}

template<class C>
static PF_Err pf_area_sample(
    PF_ProgPtr		effect_ref,		/* reference from in_data */
    PF_Fixed		x,
    PF_Fixed		y,
    const PF_SampPB	*params,
    C		*dst_pixel)
{
    aepTrace2();
    auto ins = (aepInstance*)effect_ref;
    return PF_Err_NONE;
}


////////////////////////////////////////////////////////////////
// PF World Suite
////////////////////////////////////////////////////////////////

// v1
static PF_Err pf_new_world(
    PF_ProgPtr			effect_ref,		/* reference from in_data */
    A_long				width,
    A_long				height,
    PF_NewWorldFlags	flags,			/* should would be pre-cleared to zeroes */
    PF_EffectWorld		*world)		/* always 32 bit */
{
    aepTrace2();
    return PF_Err_NONE;
}

static PF_Err pf_dispose_world(
    PF_ProgPtr		effect_ref,		/* reference from in_data */
    PF_EffectWorld		*world)
{
    aepTrace2();
    return PF_Err_NONE;
}

// v2
static PF_Err pf_NewWorld(
    PF_ProgPtr			effect_ref,				/* reference from in_data */
    A_long				widthL,
    A_long				heightL,
    PF_Boolean			clear_pixB,
    PF_PixelFormat		pixel_format,
    PF_EffectWorld		*worldP)
{
    aepTrace2();
    return PF_Err_NONE;
}

static PF_Err pf_DisposeWorld(
    PF_ProgPtr			effect_ref,				/* reference from in_data */
    PF_EffectWorld		*worldP)
{
    aepTrace2();
    return PF_Err_NONE;
}


static PF_Err pf_GetPixelFormat(
    const PF_EffectWorld		*worldP,				/* the pixel buffer of interest */
    PF_PixelFormat				*pixel_formatP)		/* << OUT. one of the above PF_PixelFormat types */
{
    aepTrace2();
    return PF_Err_NONE;
}

////////////////////////////////////////////////////////////////
// PF Pixel Format Suite
////////////////////////////////////////////////////////////////

static PF_Err pf_AddSupportedPixelFormat(
    PF_ProgPtr			effect_ref,					/* reference from in_data */
    PF_PixelFormat		pixel_format)				/* add a supported pixel format */
{
    aepTrace2();
    return PF_Err_NONE;
}

static PF_Err pf_ClearSupportedPixelFormats(
    PF_ProgPtr			effect_ref)				/* reference from in_data */
{
    aepTrace2();
    return PF_Err_NONE;
}


////////////////////////////////////////////////////////////////
// PF Iterate Suite
////////////////////////////////////////////////////////////////

template<class C>
static PF_Err pf_iterate(
    PF_InData		*in_data,
    A_long			progress_base,
    A_long			progress_final,
    PF_EffectWorld	*src,
    const PF_Rect	*area,			/* pass NULL for all pixels */
    void*		refcon,
    typename aepPixelTraits<C>::iter_t pix_fn,
    PF_EffectWorld	*dst)
{
    aepTrace2();
    return PF_Err_NONE;
}

template<class C>
static PF_Err pf_iterate_origin(
    PF_InData		*in_data,
    A_long			progress_base,
    A_long			progress_final,
    PF_EffectWorld	*src,
    const PF_Rect	*area,			/* pass NULL for all pixels */
    const PF_Point	*origin,
    void*		refcon,
    typename aepPixelTraits<C>::iter_t pix_fn,
    PF_EffectWorld	*dst)
{
    aepTrace2();
    return PF_Err_NONE;
}

template<class C>
static PF_Err pf_iterate_lut(
    PF_InData		*in_data,
    A_long			progress_base,
    A_long			progress_final,
    PF_EffectWorld	*src,
    const PF_Rect	*area,			/* pass NULL for all pixels */
    typename aepPixelTraits<C>::elem_t	*a_lut0,		/* pass NULL for identity */
    typename aepPixelTraits<C>::elem_t	*r_lut0,		/* pass NULL for identity */
    typename aepPixelTraits<C>::elem_t	*g_lut0,		/* pass NULL for identity */
    typename aepPixelTraits<C>::elem_t	*b_lut0,		/* pass NULL for identity */
    PF_EffectWorld	*dst)
{
    aepTrace2();
    return PF_Err_NONE;
}

template<class C>
static PF_Err pf_iterate_origin_non_clip_src(
    PF_InData		*in_data,
    A_long			progress_base,
    A_long			progress_final,
    PF_EffectWorld	*src,
    const PF_Rect	*area,
    const PF_Point	*origin,
    void*		refcon,
    typename aepPixelTraits<C>::iter_t pix_fn,
    PF_EffectWorld	*dst)
{
    aepTrace2();
    return PF_Err_NONE;
}

static PF_Err pf_iterate_generic(
    A_long			iterationsL,						/* >> */		// can be PF_Iterations_ONCE_PER_PROCESSOR
    void			*refconPV,							/* >> */
    PF_Err(*fn_func)(void *refconPV,			/* >> */
        A_long thread_indexL,		// only call abort and progress from thread_indexL == 0.
        A_long i,
        A_long iterationsL))
{
    aepTrace2();
    return PF_Err_NONE;
}


////////////////////////////////////////////////////////////////
// PF World Transform Suite
////////////////////////////////////////////////////////////////

static PF_Err pf_composite_rect(
    PF_ProgPtr		effect_ref,		/* from in_data */
    PF_Rect			*src_rect,		/* rectangle in source image */
    A_long			src_opacity,	/* opacity of src */
    PF_EffectWorld	*source_wld,	/* src PF world */
    A_long			dest_x,			/* upper left-hand corner of src rect...*/
    A_long			dest_y,			/* ... in composite image */
    PF_Field		field_rdr,		/* which scanlines to render (all, upper, lower) */
    PF_XferMode		xfer_mode,		/* Copy, Composite Behind, Composite In Front */
    PF_EffectWorld	*dest_wld)		/* Destination buffer. Already filled */
{
    aepTrace2();
    return PF_Err_NONE;
}

static PF_Err pf_blend(
    PF_ProgPtr		effect_ref,		/* reference from in_data */
    const PF_EffectWorld	*src1,
    const PF_EffectWorld	*src2,
    PF_Fixed		ratio,			/* 0 == full src1, 0x00010000 == full src2 */
    PF_EffectWorld	*dst)
{
    aepTrace2();
    return PF_Err_NONE;
}

static PF_Err pf_convolve(
    PF_ProgPtr		effect_ref,		/* reference from in_data */
    PF_EffectWorld	*src,
    const PF_Rect	*area,			/* pass NULL for all pixels */
    PF_KernelFlags	flags,
    A_long			kernel_size,
    void			*a_kernel,
    void			*r_kernel,
    void			*g_kernel,
    void			*b_kernel,
    PF_EffectWorld	*dst)
{
    aepTrace2();
    return PF_Err_NONE;
}

static PF_Err pf_copy(
    PF_ProgPtr		effect_ref,		/* reference from in_data	*/
    PF_EffectWorld	*src,
    PF_EffectWorld	*dst,
    PF_Rect 		*src_r,			/* pass NULL for whole world */
    PF_Rect			*dst_r)		/* pass NULL for whole world */
{
    aepTrace2();
    return PF_Err_NONE;
}

static PF_Err pf_copy_hq(
    PF_ProgPtr		effect_ref,		/* reference from in_data	*/
    PF_EffectWorld	*src,
    PF_EffectWorld	*dst,
    PF_Rect 		*src_r,			/* pass NULL for whole world */
    PF_Rect			*dst_r)		/* pass NULL for whole world */
{
    aepTrace2();
    return PF_Err_NONE;
}

static PF_Err pf_transfer_rect(
    PF_ProgPtr				effect_ref,
    PF_Quality				quality,
    PF_ModeFlags			m_flags,
    PF_Field				field,
    const PF_Rect			*src_rec,
    const PF_EffectWorld	*src_world,
    const PF_CompositeMode	*comp_mode,
    const PF_MaskWorld		*mask_world0,
    A_long					dest_x,
    A_long					dest_y,
    PF_EffectWorld			*dst_world)
{
    aepTrace2();
    return PF_Err_NONE;
}

static PF_Err pf_transform_world(
    PF_ProgPtr				effect_ref,
    PF_Quality				quality,
    PF_ModeFlags			m_flags,
    PF_Field				field,
    const PF_EffectWorld	*src_world,
    const PF_CompositeMode	*comp_mode,
    const PF_MaskWorld		*mask_world0,
    const PF_FloatMatrix	*matrices,
    A_long					num_matrices,
    PF_Boolean				src2dst_matrix,
    const PF_Rect			*dest_rect,
    PF_EffectWorld			*dst_world)
{
    aepTrace2();
    return PF_Err_NONE;
}


////////////////////////////////////////////////////////////////
// PF Fill Matte Suite
////////////////////////////////////////////////////////////////

template<class C>
static PF_Err pf_fill(
    PF_ProgPtr		effect_ref,		/* reference from in_data	*/
    const C	*color,
    const PF_Rect	*dst_rect,		/* pass NULL for whole world */
    PF_EffectWorld	*world)
{
    auto ins = (aepInstance*)effect_ref;
    aepTrace("instance: %p", ins);
    return PF_Err_NONE;
}

static PF_Err pf_premultiply(
    PF_ProgPtr		effect_ref,		/* reference from in_data */
    A_long			forward,		/* TRUE means convert non-premul to premul, FALSE mean reverse */
    PF_EffectWorld	*dst)
{
    auto ins = (aepInstance*)effect_ref;
    aepTrace("instance: %p", ins);
    return PF_Err_NONE;
}

template<class C>
static PF_Err pf_premultiply_color(
    PF_ProgPtr		effect_ref,		/* reference from in_data */
    PF_EffectWorld	*src,
    const C	*color,			/* color to premultiply/unmultiply with */
    A_long			forward,		/* TRUE means convert non-premul to premul, FALSE mean reverse */
    PF_EffectWorld	*dst)
{
    auto ins = (aepInstance*)effect_ref;
    aepTrace("instance: %p", ins);
    return PF_Err_NONE;
}


////////////////////////////////////////////////////////////////
// PICA
////////////////////////////////////////////////////////////////

static SPErr SPAcquireSuite(const char *name, int version, const void **suite)
{
    aepTrace("name: %s", name);

    typedef std::map<int, std::vector<void*>> versions;
    typedef std::map<std::string, versions> suites;
    static suites s_suites;
    if (s_suites.empty()) {
        s_suites["PF Handle Suite"][2] = { pf_host_new_handle, pf_host_lock_handle, pf_host_unlock_handle, pf_host_dispose_handle, pf_host_get_handle_size, pf_host_resize_handle };
        s_suites["PF ANSI Suite"][1] = { pf_atan, pf_atan2, pf_ceil, pf_cos, pf_exp, pf_fabs, pf_floor, pf_fmod, pf_hypot, pf_log, pf_log10, pf_pow, pf_sin, pf_sqrt, pf_tan, pf_sprintf, pf_strcpy, pf_asin, pf_acos };
        s_suites["PF Pixel Data Suite"][1] = { pf_get_pixel_data<PF_Pixel>, pf_get_pixel_data<PF_Pixel16>, pf_get_pixel_data<PF_PixelFloat> };
        s_suites["PF Color Suite"][1] = { pf_RGBtoHLS<PF_Pixel>, pf_HLStoRGB<PF_Pixel>, pf_RGBtoYIQ<PF_Pixel>, pf_YIQtoRGB<PF_Pixel>, pf_Luminance<PF_Pixel>, pf_Hue<PF_Pixel>, pf_Lightness<PF_Pixel>, pf_Saturation<PF_Pixel> };
        s_suites["PF Color16 Suite"][1] = { pf_RGBtoHLS<PF_Pixel16>, pf_HLStoRGB<PF_Pixel16>, pf_RGBtoYIQ<PF_Pixel16>, pf_YIQtoRGB<PF_Pixel16>, pf_Luminance<PF_Pixel16>, pf_Hue<PF_Pixel16>, pf_Lightness<PF_Pixel16>, pf_Saturation<PF_Pixel16> };
        s_suites["PF ColorFloat Suite"][1] = { pf_RGBtoHLS<PF_PixelFloat>, pf_HLStoRGB<PF_PixelFloat>, pf_RGBtoYIQ<PF_PixelFloat>, pf_YIQtoRGB<PF_PixelFloat>, pf_Luminance<PF_PixelFloat>, pf_Hue<PF_PixelFloat>, pf_Lightness<PF_PixelFloat>, pf_Saturation<PF_PixelFloat> };
        s_suites["PF Batch Sampling Suite"][1] = { pf_begin_sampling, pf_end_sampling, pf_get_batch_func<PF_Pixel>, pf_get_batch_func<PF_Pixel16> };
        s_suites["PF Sampling8 Suite"][1] = { pf_nn_sample<PF_Pixel>, pf_subpixel_sample<PF_Pixel>, pf_area_sample<PF_Pixel> };
        s_suites["PF Sampling16 Suite"][1] = { pf_nn_sample<PF_Pixel16>, pf_subpixel_sample<PF_Pixel16>, pf_area_sample<PF_Pixel16> };
        s_suites["PF SamplingFloat Suite"][1] = { pf_nn_sample<PF_PixelFloat>, pf_subpixel_sample<PF_PixelFloat>, pf_area_sample<PF_PixelFloat> };
        s_suites["PF World Suite"][1] = { pf_new_world, pf_dispose_world };
        s_suites["PF World Suite"][2] = { pf_NewWorld, pf_DisposeWorld, pf_GetPixelFormat };
        s_suites["PF Pixel Format Suite"][2] = { pf_AddSupportedPixelFormat, pf_ClearSupportedPixelFormats };
        s_suites["PF Iterate8 Suite"][1] = { pf_iterate<PF_Pixel>, pf_iterate_origin<PF_Pixel>, pf_iterate_lut<PF_Pixel>, pf_iterate_origin_non_clip_src<PF_Pixel>, pf_iterate_generic };
        s_suites["PF iterate16 Suite"][1] = { pf_iterate<PF_Pixel16>, pf_iterate_origin<PF_Pixel16>, pf_iterate_lut<PF_Pixel16>, pf_iterate_origin_non_clip_src<PF_Pixel16>, pf_iterate_generic };
        s_suites["PF iterateFloat Suite"][1] = { pf_iterate<PF_PixelFloat>, pf_iterate_origin<PF_PixelFloat>, pf_iterate_lut<PF_PixelFloat>, pf_iterate_origin_non_clip_src<PF_PixelFloat>, pf_iterate_generic };
        s_suites["PF World Transform Suite"][1] = { pf_composite_rect, pf_blend, pf_convolve, pf_copy, pf_copy_hq, pf_transfer_rect, pf_transform_world };
        s_suites["PF Fill Matte Suite"][2] = { pf_fill<PF_Pixel>, pf_fill<PF_Pixel16>, pf_fill<PF_PixelFloat>, pf_premultiply, pf_premultiply_color<PF_Pixel>, pf_premultiply_color<PF_Pixel16>, pf_premultiply_color<PF_PixelFloat> };
    }
    auto i = s_suites.find(name);
    if (i != s_suites.end()) {
        versions& vs = i->second;
        auto v = vs.find(version);
        if (v != vs.end()) {
            *suite = &v->second[0];
        }
        else {
            *suite = &(vs.begin()->second[0]);
        }
    }
    return kSPNoError;
}
static SPErr SPReleaseSuite(const char *name, int version)
{
    aepTrace("name: %s", name);
    return kSPNoError;
}
static SPBoolean SPIsEqual(const char *token1, const char *token2)
{
    aepTrace("token1: %s, token2: %s", token1, token2);
    return 0;
}
static SPErr SPAllocateBlock(size_t size, void **block)
{
    aepTrace("size: %u", (uint32_t)size);
    *block = malloc(size);
    return kSPNoError;
}
static SPErr SPFreeBlock(void *block)
{
    aepTrace("block: %p", block);
    free(block);
    return kSPNoError;
}
static SPErr SPReallocateBlock(void *block, size_t newSize, void **newblock)
{
    aepTrace("block: %p, newSize", block, (uint32_t)newSize);
    *newblock = realloc(block, newSize);
    return kSPNoError;
}
static SPErr SPUndefined(void)
{
    aepTrace2();
    return kSPNoError;
}


////////////////////////////////////////////////////////////////
// interface
////////////////////////////////////////////////////////////////

PF_InteractCallbacks& aepGetHostCallbacks()
{
    static PF_InteractCallbacks s_host_cb;
    if (!s_host_cb.checkout_param) {
#define def(F) s_host_cb.F = pf_##F
def(checkout_param);
def(checkin_param);
def(add_param);
def(abort);
def(progress);
def(register_ui);
def(checkout_layer_audio);
def(checkin_layer_audio);
def(get_audio_data);
#undef def
    }
    return s_host_cb;
}

PF_UtilCallbacks& aepGetUtilCallbacks()
{
    static PF_UtilCallbacks s_util_cb;
    if (!s_util_cb.begin_sampling) {
#define def(F) s_util_cb.F = pf_##F
#define def2(F1, F2) s_util_cb.F1 = F2
def(begin_sampling);
def2(subpixel_sample, pf_subpixel_sample<PF_Pixel>);
def2(area_sample, pf_area_sample<PF_Pixel>);
def(end_sampling);
def(composite_rect);
def(blend);
def(convolve);
def(copy);
def2(fill, pf_fill<PF_Pixel>);
def(gaussian_kernel);
def2(iterate, pf_iterate<PF_Pixel>);
def(premultiply);
def2(premultiply_color, pf_premultiply_color<PF_Pixel>);
def(new_world);
def(dispose_world);
def2(iterate_origin, pf_iterate_origin<PF_Pixel>);
def2(iterate_lut, pf_iterate_lut<PF_Pixel>);
def(transfer_rect);
def(transform_world);
def(host_new_handle);
def(host_lock_handle);
def(host_unlock_handle);
def(host_dispose_handle);
def(get_callback_addr);
def(app);
def(get_platform_data);
def(host_get_handle_size);
def2(iterate_origin_non_clip_src, pf_iterate_origin_non_clip_src<PF_Pixel>);
def(iterate_generic);
def(host_resize_handle);
def2(subpixel_sample16, pf_subpixel_sample<PF_Pixel16>);
def2(area_sample16, pf_area_sample<PF_Pixel16>);
def2(fill16, pf_fill<PF_Pixel16>);
def2(premultiply_color16, pf_premultiply_color<PF_Pixel16>);
def2(iterate16, pf_iterate<PF_Pixel16>);
def2(iterate_origin16, pf_iterate_origin<PF_Pixel16>);
def2(iterate_origin_non_clip_src16, pf_iterate_origin_non_clip_src<PF_Pixel16>);
def2(get_pixel_data8, pf_get_pixel_data<PF_Pixel>);
def2(get_pixel_data16, pf_get_pixel_data<PF_Pixel16>);
#undef def
#define def(F) s_util_cb.ansi.F = pf_##F
def(atan);
def(atan2);
def(ceil);
def(cos);
def(exp);
def(fabs);
def(floor);
def(fmod);
def(hypot);
def(log);
def(log10);
def(pow);
def(sin);
def(sqrt);
def(tan);
def(sprintf);
def(strcpy);
def(asin);
def(acos);
#undef def
#define def(F) s_util_cb.colorCB.F = pf_##F
def(RGBtoHLS);
def(HLStoRGB);
def(RGBtoYIQ);
def(YIQtoRGB);
def(Luminance);
def(Hue);
def(Lightness);
def(Saturation);
#undef def
    }
    return s_util_cb;
}

SPBasicSuite& aepGetSPBasicSuite()
{
    static SPBasicSuite s_sp;
    if (!s_sp.AcquireSuite) {
#define def(F) s_sp.F = SP##F
def(AcquireSuite);
def(ReleaseSuite);
def(IsEqual);
def(AllocateBlock);
def(FreeBlock);
def(ReallocateBlock);
def(Undefined);
#undef def
    }
    return s_sp;
}
