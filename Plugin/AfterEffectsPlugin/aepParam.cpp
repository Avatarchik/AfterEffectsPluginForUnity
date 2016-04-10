#include "pch.h"
#include "aepInternal.h"

aepParam::aepParam(aepInstance *inst, const PF_ParamDef& pf)
    : m_inst(inst)
    , m_type()
{
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
    return &m_bool;
}

void aepParam::setup(const PF_ParamDef& pf)
{
    m_pf = pf;
    auto& u = m_pf.u;

    switch (m_pf.param_type) {
    case PF_Param_CHECKBOX:
        m_type = aepParamType_Bool;
        m_bool.value = m_bool.def = u.bd.dephault != 0;
        break;
    case PF_Param_FLOAT_SLIDER:
        m_type = aepParamType_Double;
        m_double.value = m_double.def = u.fs_d.dephault;
        m_double.min = u.fs_d.valid_min;
        m_double.max = u.fs_d.valid_max;
        break;
    case PF_Param_SLIDER:
        m_type = aepParamType_Int;
        m_int.value = m_int.def = u.sd.dephault;
        m_int.min = u.sd.valid_min;
        m_int.max = u.sd.valid_max;
        break;
    case PF_Param_FIX_SLIDER:
        m_type = aepParamType_Int;
        m_int.value = m_int.def = u.fd.dephault;
        m_int.min = u.fd.valid_min;
        m_int.max = u.fd.valid_max;
        break;
    case PF_Param_ANGLE:
        m_type = aepParamType_Int;
        m_int.value = m_int.def = u.ad.dephault;
        break;
    case PF_Param_POINT:
        m_type = aepParamType_Point2D;
        m_point2d.value = m_point2d.def = aepPoint2D(u.td.x_dephault, u.td.y_dephault);
        break;
    case PF_Param_POINT_3D:
        m_type = aepParamType_Point3D;
        m_point3d.value = m_point3d.def = aepPoint3D(u.point3d_d.x_dephault, u.point3d_d.y_dephault, u.point3d_d.z_dephault);
        break;
    case PF_Param_COLOR:
        m_type = aepParamType_Color;
        m_color.value = m_color.def = (aepColor&)u.cd.dephault;
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
    case aepParamType_Bool:     *((aepBoolValue*)dst) = m_bool; break;
    case aepParamType_Int:      *((aepIntValue*)dst) = m_int; break;
    case aepParamType_Double:   *((aepDoubleValue*)dst) = m_double; break;
    case aepParamType_Point2D:  *((aepPoint2DValue*)dst) = m_point2d; break;
    case aepParamType_Point3D:  *((aepPoint3DValue*)dst) = m_point3d; break;
    case aepParamType_Color:    *((aepColorValue*)dst) = m_color; break;
    }
}

void aepParam::setValue(const void *src)
{
    auto& u = m_pf.u;
    switch (m_type) {
    case aepParamType_Bool:
        u.bd.value = (int)((aepBoolValue*)src)->value;
        break;
    case aepParamType_Int:
        u.sd.value = ((aepIntValue*)src)->value;
        break;
    case aepParamType_Double:
        u.fs_d.value = ((aepDoubleValue*)src)->value;
        break;
    case aepParamType_Point2D:
        u.td.x_value = ((aepPoint2DValue*)src)->value.x;
        u.td.y_value = ((aepPoint2DValue*)src)->value.y;
        break;
    case aepParamType_Point3D:
        u.point3d_d.x_value = ((aepPoint3DValue*)src)->value.x;
        u.point3d_d.y_value = ((aepPoint3DValue*)src)->value.y;
        u.point3d_d.z_value = ((aepPoint3DValue*)src)->value.z;
        break;
    case aepParamType_Color:
        u.cd.value = (PF_Pixel&)((aepColorValue*)src)->value;
        break;
    }
}
