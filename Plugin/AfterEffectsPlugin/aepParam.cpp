#include "pch.h"
#include "aepInternal.h"

aepParam::aepParam(aepInstance *inst)
    : m_inst(inst)
    , m_type()
{
}

aepParam::~aepParam()
{
}

const char* aepParam::getName() const { return m_pf.name; }
aepParamType aepParam::getType() const { return m_type; }
PF_ParamDef& aepParam::getPFParamDef() { return m_pf; }

void* aepParam::getDataPtr()
{
    return &m_bool;
}

void aepParam::setup()
{
    auto& u = m_pf.u;

    switch (m_pf.param_type) {
    case PF_Param_CHECKBOX:
        m_type = aepParamType_Bool;
        break;
    case PF_Param_FLOAT_SLIDER:
        m_type = aepParamType_Float;
        break;
    case PF_Param_SLIDER:
        m_type = aepParamType_Float;
        break;
    case PF_Param_FIX_SLIDER:
        m_type = aepParamType_Float;
        break;
    case PF_Param_ANGLE:
        m_type = aepParamType_Float;
        m_int.def = u.ad.dephault;
        break;
    case PF_Param_POINT:
        m_type = aepParamType_Point2D;
        m_point2d.value = aepPoint2D(u.td.x_value, u.td.y_value);
        m_point2d.def = aepPoint2D(u.td.x_dephault, u.td.y_dephault);
        break;
    case PF_Param_POINT_3D:
        m_type = aepParamType_Point3D;
        m_point3d.value = aepPoint3D(u.point3d_d.x_value, u.point3d_d.y_value, u.point3d_d.z_value);
        m_point3d.def = aepPoint3D(u.point3d_d.x_dephault, u.point3d_d.y_dephault, u.point3d_d.z_dephault);
        break;
    case PF_Param_COLOR:
        m_type = aepParamType_Color;
        break;
    case PF_Param_PATH:
        m_type = aepParamType_Path;
        break;
    case PF_Param_LAYER:
        m_type = aepParamType_Layer;
        break;
    }
}
void aepParam::copyToPF()
{

}
void aepParam::copyFromPF()
{

}

void aepParam::getValue(void *dst)
{
    switch (m_type) {
    case aepParamType_Bool:     *((aepBoolValue*)dst) = m_bool; break;
    case aepParamType_Float:    *((aepIntValue*)dst) = m_int; break;
    case aepParamType_Point2D:  *((aepPoint2DValue*)dst) = m_point2d; break;
    case aepParamType_Point3D:  *((aepPoint3DValue*)dst) = m_point3d; break;
    case aepParamType_Color:    *((aepColorValue*)dst) = m_color; break;
    }
}

void aepParam::setValue(const void *src)
{
    switch (m_type) {
    case aepParamType_Bool:     m_bool.value = ((aepBoolValue*)src)->value; break;
    case aepParamType_Float:    m_int.value = ((aepIntValue*)src)->value; break;
    case aepParamType_Point2D:  m_point2d.value = ((aepPoint2DValue*)src)->value; break;
    case aepParamType_Point3D:  m_point3d.value = ((aepPoint3DValue*)src)->value; break;
    case aepParamType_Color:    m_color.value = ((aepColorValue*)src)->value; break;
    }
}

void aepParam::apply()
{
    // todo
}
