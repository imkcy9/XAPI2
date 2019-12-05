//
// Created by kecy on 2019/12/5.
//
#include "../../../include/FIRSTApi.h"

#include "FIRSTApiImpl.h"

//FIRSTApi::FIRSTApi()
//{
//}
//
//FIRSTApi::~FIRSTApi()
//{
//}

FIRSTApi* FIRSTApi::CreateApi(const char* libPath)
{
    return new FIRSTApiImpl(libPath);
}