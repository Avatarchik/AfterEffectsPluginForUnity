#include "pch.h"
#include "Foundation.h"
#include "AfterEffectsPlugin.h"
#include "aepModule.h"
#include "aepInstance.h"
#include "aepParam.h"

aepParam::aepParam(aepInstance *inst)
    : m_inst(inst)
{
}

aepParam::~aepParam()
{
}

const std::string& aepParam::getName() const { return m_name; }
aepParamType aepParam::getType() const { return m_type; }

void* aepParam::getDataPtr()
{
    return &m_bool;
}



void aepParam::getValue(void *dst)
{
    switch (m_type) {
    case aepParamType_Bool:     *((aepBoolValue*)dst) = m_bool; break;
    case aepParamType_Float:    *((aepFloatValue*)dst) = m_float; break;
    case aepParamType_Point2D:  *((aepPoint2DValue*)dst) = m_point2d; break;
    case aepParamType_Point3D:  *((aepPoint3DValue*)dst) = m_point3d; break;
    case aepParamType_Color:    *((aepColorValue*)dst) = m_color; break;
    }
}

void aepParam::setValue(const void *src)
{
    switch (m_type) {
    case aepParamType_Bool:     m_bool = *((aepBoolValue*)src); break;
    case aepParamType_Float:    m_float = *((aepFloatValue*)src); break;
    case aepParamType_Point2D:  m_point2d = *((aepPoint2DValue*)src); break;
    case aepParamType_Point3D:  m_point3d = *((aepPoint3DValue*)src); break;
    case aepParamType_Color:    m_color = *((aepColorValue*)src); break;
    }
}

void aepParam::apply()
{
    // todo
}
