#include "pch.h"
#include "Foundation.h"
#include "AfterEffectsPlugin.h"
#include "aepModule.h"
#include "aepInstance.h"
#include "aepParam.h"

aepParam::aepParam()
{
}

aepParam::~aepParam()
{
}

const aepParamInfo& aepParam::getInfo() const
{
    return m_info;
}

void* aepParam::getDataPtr()
{
    return &m_bool;
}

void aepParam::getValue(void *dst)
{
    // todo
}

void aepParam::setValue(const void *src)
{
    // todo
}
