//
// Created by kecy on 2019/12/5.
//

#if defined WINDOWS || _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <stdio.h>
#include <time.h>
#include <string.h>

#include "../../../include/FIRSTApi.h"

#ifndef USE_CMAKE
#ifdef _WIN64
#pragma comment(lib, "../../lib/XAPI_CPP_x64.lib")
#else
#pragma comment(lib, "../../lib/XAPI_CPP_x86.lib")
#endif
#endif

class FIRSTSpiImpl :public FIRSTSpi
{
public:
    FIRSTSpiImpl() :FIRSTSpi()
    {
        count = 0;
    }

    virtual void OnFrontConnected(){
        printf("OnFrontConnected\r\n");
    };

    void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                        bool bIsLast) override {
        FIRSTSpi::OnRspUserLogin(pRspUserLogin, pRspInfo, nRequestID, bIsLast);
    }

    void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo,
                            int nRequestID, bool bIsLast) override {
        FIRSTSpi::OnRspSubMarketData(pSpecificInstrument, pRspInfo, nRequestID, bIsLast);
    }

    void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) override {
        printf("OnRtnDepthMarketData %s \n", pDepthMarketData->InstrumentID);
    }

public:
    //CXApi* m_pApi;
    int count;
};

int main(int argc, char* argv[])
{
#if _WIN32
    #if _WIN64
	char DLLPath1[250] = "CTP_Quote_x64.dll";
	char DLLPath2[250] = "CTP_Trade_x64.dll";
#else
	char DLLPath1[250] = "CTP_Quote_x86.dll";
	char DLLPath2[250] = "CTP_Trade_x86.dll";
#endif
#else
    char DLLPath1[1024] = "libCTP_SE_Quote.so";
    //char DLLPath2[1024] = "libCTP_Trade.so";
//	char dir_path[512] = {0};
//	char DLLPath1[1024] = {0};
//	char DLLPath2[1024] = {0};
//
//	if (getcwd(dir_path, sizeof(dir_path)) == NULL)
//	{
//		return 1;
//	}
//	snprintf(DLLPath1, sizeof(DLLPath1), "%s/libCTP_Quote.so", dir_path);
//	snprintf(DLLPath2, sizeof(DLLPath2), "%s/libCTP_Trade.so", dir_path);
#endif


//    strcpy(m_ServerInfo1.BrokerID, "4040");
//    strcpy(m_ServerInfo1.Address, "tcp://yhzx-front1.yhqh.com:41213;tcp://yhzx-front3.yhqh.com:41213");
//
//    strcpy(m_ServerInfo2.BrokerID, "4040");
//    strcpy(m_ServerInfo2.Address, "tcp://yhzx-front1.yhqh.com:51205;tcp://yhzx-front3.yhqh.com:52205");
//
//    strcpy(m_UserInfo.UserID, "00000025");
//    strcpy(m_UserInfo.Password, "123456");



    while (true)
    {
        FIRSTApi* pApi1 = FIRSTApi::CreateApi(DLLPath1);
        //FIRSTApi* pApi2 = FIRSTApi::CreateApi(DLLPath2);

        if (!pApi1->Init())
        {
            //printf("%s\r\n", pApi1->GetLastError());
            //pApi1->Disconnect();
            break;
        }

        //if (!pApi2->Init())
        {
            //printf("%s\r\n", pApi2->GetLastError());
            //pApi2->Disconnect();
            //break;
        }
        FIRSTSpi *p = new FIRSTSpiImpl();
        pApi1->RegisterSpi(p);
        CThostFtdcReqAuthenticateField reqAuthenticateField = {};
        CThostFtdcReqUserLoginField reqUserLoginField = {};
        strcpy(reqUserLoginField.BrokerID, "9999");
        strcpy(reqUserLoginField.UserID, "005890");
        strcpy(reqUserLoginField.Password, "123456");

        //180.168.146.187:10131 tcp://218.202.237.33:10112
        pApi1->connect("tcp://180.168.146.187:10131", &reqAuthenticateField, &reqUserLoginField);
        //pApi1->RegisterFront("tcp://yhzx-front1.yhqh.com:41213;tcp://yhzx-front3.yhqh.com:41213");
        //pApi1->Connect("./", &m_ServerInfo1, &m_UserInfo, 1);
        printf("已经执行完Connect\n");

        sleep(2);
        char* inst = "SR003";
        pApi1->SubscribeMarketData(&inst, 1);

        //pApi2->RegisterSpi(p);
        //pApi2->Connect("./", &m_ServerInfo2, &m_UserInfo, 1);
        //printf("已经执行完Connect\n");
        getchar();

        //pApi1->Disconnect();
        //pApi2->Disconnect();
        printf("已经执行完Disconnect");
        //getchar();
    }

    return 0;
}
