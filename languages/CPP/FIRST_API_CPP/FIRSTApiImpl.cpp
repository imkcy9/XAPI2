//
// Created by kecy on 2019/12/5.
//

#include "FIRSTApiImpl.h"
#include "../../../include/QueueEnum.h"
#include "FIRSTApiC.cpp"
void* __stdcall FIRSTApiImpl::OnResponse(char type, void* pApi1, void* pApi2, double double1, double double2, void* ptr1, int size1, void* ptr2, int size2, void* ptr3, int size3)
{
    if (pApi2 == nullptr)
        return nullptr;

    FIRSTApiImpl* pThisClass = (FIRSTApiImpl*)pApi2;
    return pThisClass->_OnResponse(type, pApi1, pApi2, double1, double2, ptr1, size1, ptr2, size2, ptr3, size3);
}

void* FIRSTApiImpl::_OnResponse(char type, void* pApi1, void* pApi2, double double1, double double2, void* ptr1, int size1, void* ptr2, int size2, void* ptr3, int size3)
{
    if (nullptr == m_pSpi)
        return nullptr;

    ResponseType rt = (ResponseType)type;
    switch (rt)
    {
        case ResponseType_OnConnectionStatus:
            m_pSpi->OnFrontConnected();
            break;
        case ResponseType_OnRtnError:
            m_pSpi->OnRspError((CThostFtdcRspInfoField*)ptr1, size1, size2);
            break;
        case ResponseType_OnLog:
            //m_pSpi->OnLog(this, (LogField*)ptr1);
            break;
        case ResponseType_OnRtnDepthMarketData:
            m_pSpi->OnRtnDepthMarketData((CThostFtdcDepthMarketDataField*)ptr1);
            break;
        case ResponseType_OnRspQryInstrument:
            m_pSpi->OnRspQryInstrument((CThostFtdcInstrumentField*)ptr1, (CThostFtdcRspInfoField*)ptr2, size2, size3 != 0);
            break;
        case ResponseType_OnRspQryTradingAccount:
            //m_pSpi->OnRspQryTradingAccount(this, (AccountField*)ptr1, size1, double1 != 0);
            break;
        case ResponseType_OnRspQryInvestorPosition:
            //m_pSpi->OnRspQryInvestorPosition(this, (PositionField*)ptr1, size1, double1 != 0);
            break;
        case ResponseType_OnRspQrySettlementInfo:
            //m_pSpi->OnRspQrySettlementInfo(this, (SettlementInfoField*)ptr1, size1, double1 != 0);
            break;

        case ResponseType_OnRspQryOrder:
            //m_pSpi->OnRspQryOrder(this, (OrderField*)ptr1, size1, double1 != 0);
            break;
        case ResponseType_OnRspQryTrade:
            //m_pSpi->OnRspQryTrade(this, (TradeField*)ptr1, size1, double1 != 0);
            break;
        case ResponseType_OnRspQryQuote:
           // m_pSpi->OnRspQryQuote(this, (QuoteField*)ptr1, size1, double1 != 0);
            break;

        case ResponseType_OnRtnOrder:
            m_pSpi->OnRtnOrder((CThostFtdcOrderField*)ptr1);
            break;
        case ResponseType_OnRtnTrade:
            m_pSpi->OnRtnTrade((CThostFtdcTradeField*)ptr1);
            break;
        case ResponseType_OnRtnQuote:
            m_pSpi->OnRtnQuote((CThostFtdcQuoteField*)ptr1);
            break;

        case ResponseType_OnRtnQuoteRequest:
            //m_pSpi->OnRtnQuoteRequest(this, (QuoteRequestField*)ptr1);
            break;

        case ResponseType_OnRspQryHistoricalTicks:
            //m_pSpi->OnRspQryHistoricalTicks(this, (TickField*)ptr1, size1, (HistoricalDataRequestField*)ptr2, size2, double1 != 0);
            break;
        case ResponseType_OnRspQryHistoricalBars:
            //m_pSpi->OnRspQryHistoricalBars(this, (BarField*)ptr1, size1, (HistoricalDataRequestField*)ptr2, size2, double1 != 0);
            break;
        case ResponseType_OnRspQryInvestor:
            //m_pSpi->OnRspQryInvestor(this, (InvestorField*)ptr1, size1, double1 != 0);
            break;
        case ResponseType_OnRtnInstrumentStatus:
            m_pSpi->OnRtnInstrumentStatus((CThostFtdcInstrumentStatusField*)ptr1);
            break;

        case ResponseType_OnFilterSubscribe:
            //return (void*)m_pSpi->OnFilterSubscribe(this, (ExchangeType)(char)double1, (int)size1, (int)size1, (int)size3, (char*)ptr1);
            return nullptr;
        default:
            break;
    }
    return nullptr;
}

FIRSTApiImpl::FIRSTApiImpl(const char* libPath) {
    m_pLib = nullptr;
    m_pFun = nullptr;
    m_pApi = nullptr;
    m_pSpi = nullptr;

    strncpy(m_LibPath, libPath, sizeof(m_LibPath));
}

FIRSTApiImpl::~FIRSTApiImpl() {

}

void FIRSTApiImpl::Release() {

}

bool FIRSTApiImpl::Init() {
    m_pLib = X_LoadLib(m_LibPath);
    if (m_pLib)
    {
        m_pFun = X_GetFunction(m_pLib);
        if (m_pFun)
        {
            return true;
        }
    }
    return false;
}

int FIRSTApiImpl::Join() {
    return 0;
}

const char *FIRSTApiImpl::GetTradingDay() {
    return nullptr;
}

void FIRSTApiImpl::RegisterFront(char *pszFrontAddress) {
    m_pApi = X_Create(m_pFun);
    X_Register(m_pFun, m_pApi, (fnOnResponse)OnResponse, this);
    X_Connect(m_pFun, m_pApi, pszFrontAddress);
}

void FIRSTApiImpl::RegisterNameServer(char *pszNsAddress) {

}

void FIRSTApiImpl::RegisterFensUserInfo(CThostFtdcFensUserInfoField *pFensUserInfo) {

}

void FIRSTApiImpl::RegisterSpi(FIRSTSpi *pSpi) {
    this->m_pSpi = pSpi;
}

void FIRSTApiImpl::SubscribePrivateTopic(THOST_TE_RESUME_TYPE nResumeType) {

}

void FIRSTApiImpl::SubscribePublicTopic(THOST_TE_RESUME_TYPE nResumeType) {

}

int FIRSTApiImpl::ReqAuthenticate(CThostFtdcReqAuthenticateField *pReqAuthenticateField, int nRequestID) {
    return 0;
}

int FIRSTApiImpl::ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLoginField, int nRequestID) {
    return 0;
}

int FIRSTApiImpl::ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout, int nRequestID) {
    return 0;
}

int FIRSTApiImpl::ReqOrderInsert(CThostFtdcInputOrderField *pInputOrder, int nRequestID) {
    return 0;
}

int FIRSTApiImpl::ReqOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, int nRequestID) {
    return 0;
}

int
FIRSTApiImpl::ReqSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, int nRequestID) {
    return 0;
}

int FIRSTApiImpl::ReqForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, int nRequestID) {
    return 0;
}

int FIRSTApiImpl::ReqQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, int nRequestID) {
    return 0;
}

int FIRSTApiImpl::ReqQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, int nRequestID) {
    return 0;
}

int FIRSTApiImpl::ReqQryOrder(CThostFtdcQryOrderField *pQryOrder, int nRequestID) {
    return 0;
}

int FIRSTApiImpl::ReqQryTrade(CThostFtdcQryTradeField *pQryTrade, int nRequestID) {
    return 0;
}

int FIRSTApiImpl::ReqQryInvestorPosition(CThostFtdcQryInvestorPositionField *pQryInvestorPosition, int nRequestID) {
    return 0;
}

int FIRSTApiImpl::ReqQryTradingAccount(CThostFtdcQryTradingAccountField *pQryTradingAccount, int nRequestID) {
    return 0;
}

int FIRSTApiImpl::ReqQryInvestor(CThostFtdcQryInvestorField *pQryInvestor, int nRequestID) {
    return 0;
}

int FIRSTApiImpl::ReqQryInstrument(CThostFtdcQryInstrumentField *pQryInstrument, int nRequestID) {
    return 0;
}

int FIRSTApiImpl::ReqQryDepthMarketData(CThostFtdcQryDepthMarketDataField *pQryDepthMarketData, int nRequestID) {
    return 0;
}

int FIRSTApiImpl::ReqQrySettlementInfo(CThostFtdcQrySettlementInfoField *pQrySettlementInfo, int nRequestID) {
    return 0;
}

int FIRSTApiImpl::ReqQryInvestorPositionDetail(CThostFtdcQryInvestorPositionDetailField *pQryInvestorPositionDetail,
                                               int nRequestID) {
    return 0;
}

int FIRSTApiImpl::ReqQrySettlementInfoConfirm(CThostFtdcQrySettlementInfoConfirmField *pQrySettlementInfoConfirm,
                                              int nRequestID) {
    return 0;
}

int FIRSTApiImpl::ReqQryInvestorPositionCombineDetail(
        CThostFtdcQryInvestorPositionCombineDetailField *pQryInvestorPositionCombineDetail, int nRequestID) {
    return 0;
}

int FIRSTApiImpl::ReqQryForQuote(CThostFtdcQryForQuoteField *pQryForQuote, int nRequestID) {
    return 0;
}

int FIRSTApiImpl::ReqQryQuote(CThostFtdcQryQuoteField *pQryQuote, int nRequestID) {
    return 0;
}

int FIRSTApiImpl::SubscribeMarketData(char **ppInstrumentID, int nCount) {
    return 0;
}

int FIRSTApiImpl::UnSubscribeMarketData(char **ppInstrumentID, int nCount) {
    return 0;
}

int FIRSTApiImpl::SubscribeForQuoteRsp(char **ppInstrumentID, int nCount) {
    return 0;
}

int FIRSTApiImpl::UnSubscribeForQuoteRsp(char **ppInstrumentID, int nCount) {
    return 0;
}
