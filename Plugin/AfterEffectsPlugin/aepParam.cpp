#include "pch.h"
#include "aepInternal.h"

aepParam::aepParam(aepInstance *inst, const PF_ParamDef& pf)
    : m_inst(inst)
    , m_type()
{
    memset(&m_data, 0, sizeof(m_data));
    memset(&m_pf, 0, sizeof(m_pf));
    setup(pf);
}

aepParam::~aepParam()
{
}

const char* aepParam::getName() const { return m_pf.name; }
aepParamType aepParam::getType() const { return m_type; }
PF_ParamDef& aepParam::getPFParam() { return m_pf; }

void* aepParam::getDataPtr()
{
    return &m_data;
}

void aepParam::setup(const PF_ParamDef& pf)
{
    m_pf = pf;
    auto& u = m_pf.u;

    switch (m_pf.param_type) {
    case PF_Param_CHECKBOX:
        m_type = aepParamType_Bool;
        m_data.vbool.value = m_data.vbool.def = u.bd.dephault != 0;
        break;
    case PF_Param_FLOAT_SLIDER:
        m_type = aepParamType_Double;
        m_data.vdouble.value = m_data.vdouble.def = u.fs_d.dephault;
        m_data.vdouble.min = u.fs_d.valid_min;
        m_data.vdouble.max = u.fs_d.valid_max;
        break;
    case PF_Param_SLIDER:
        m_type = aepParamType_Int;
        m_data.vint.value = m_data.vint.def = u.sd.dephault;
        m_data.vint.min = u.sd.valid_min;
        m_data.vint.max = u.sd.valid_max;
        break;
    case PF_Param_FIX_SLIDER:
        m_type = aepParamType_Int;
        m_data.vint.value = m_data.vint.def = u.fd.dephault;
        m_data.vint.min = u.fd.valid_min;
        m_data.vint.max = u.fd.valid_max;
        break;
    case PF_Param_ANGLE:
        m_type = aepParamType_Int;
        m_data.vint.value = m_data.vint.def = u.ad.dephault;
        break;
    case PF_Param_POINT:
        m_type = aepParamType_Point2D;
        m_data.vpoint2d.value = m_data.vpoint2d.def = { u.td.x_dephault, u.td.y_dephault };
        break;
    case PF_Param_POINT_3D:
        m_type = aepParamType_Point3D;
        m_data.vpoint3d.value = m_data.vpoint3d.def = { u.point3d_d.x_dephault, u.point3d_d.y_dephault, u.point3d_d.z_dephault };
        break;
    case PF_Param_COLOR:
        m_type = aepParamType_Color;
        m_data.vcolor.value = m_data.vcolor.def = (aepColor&)u.cd.dephault;
        break;
    case PF_Param_PATH:
        m_type = aepParamType_Path;
        break;
    case PF_Param_LAYER:
        m_type = aepParamType_Layer;
        break;
    }
}

void aepParam::getValue(void *dst)
{
    switch (m_type) {
    case aepParamType_Bool:     *((aepBoolParamValue*)dst) = m_data.vbool; break;
    case aepParamType_Int:      *((aepIntParamValue*)dst) = m_data.vint; break;
    case aepParamType_Double:   *((aepDoubleParamValue*)dst) = m_data.vdouble; break;
    case aepParamType_Point2D:  *((aepPoint2DParamValue*)dst) = m_data.vpoint2d; break;
    case aepParamType_Point3D:  *((aepPoint3DParamValue*)dst) = m_data.vpoint3d; break;
    case aepParamType_Color:    *((aepColorParamValue*)dst) = m_data.vcolor; break;
    case aepParamType_Layer:    *((aepLayerParamValue*)dst) = m_data.vlayer; break;
    }
}

void aepParam::setValue(const void *src)
{
    auto& u = m_pf.u;
    switch (m_type) {
    case aepParamType_Bool:
        m_data.vbool.value = ((aepBoolParamValue*)src)->value;
        u.bd.value = m_data.vbool.value;
        break;
    case aepParamType_Int:
        m_data.vint.value = ((aepIntParamValue*)src)->value;
        if (m_data.vint.min != m_data.vint.max) {
            m_data.vint.value = std::min<int>(std::max<int>(m_data.vint.value, m_data.vint.min), m_data.vint.max);
        }
        u.sd.value = m_data.vint.value;
        break;
    case aepParamType_Double:
        m_data.vdouble.value = ((aepDoubleParamValue*)src)->value;
        if (m_data.vdouble.min != m_data.vdouble.max) {
            m_data.vdouble.value = std::min<double>(std::max<double>(m_data.vdouble.value, m_data.vdouble.min), m_data.vdouble.max);
        }
        u.fs_d.value = m_data.vdouble.value;
        break;
    case aepParamType_Point2D:
        m_data.vpoint2d.value = ((aepPoint2DParamValue*)src)->value;
        u.td.x_value = m_data.vpoint2d.value.x;
        u.td.y_value = m_data.vpoint2d.value.y;
        break;
    case aepParamType_Point3D:
        m_data.vpoint3d.value = ((aepPoint3DParamValue*)src)->value;
        u.point3d_d.x_value = m_data.vpoint3d.value.x;
        u.point3d_d.y_value = m_data.vpoint3d.value.y;
        u.point3d_d.z_value = m_data.vpoint3d.value.z;
        break;
    case aepParamType_Color:
        m_data.vcolor.value = ((aepColorParamValue*)src)->value;
        u.cd.value.alpha = m_data.vcolor.value.a;
        u.cd.value.red   = m_data.vcolor.value.r;
        u.cd.value.green = m_data.vcolor.value.g;
        u.cd.value.blue  = m_data.vcolor.value.b;
        break;
    case aepParamType_Layer:
        m_data.vlayer.value = ((aepLayerParamValue*)src)->value;
        if (m_data.vlayer.value) {
            u.ld = m_data.vlayer.value->getPF();
        }
        break;
    }
}
