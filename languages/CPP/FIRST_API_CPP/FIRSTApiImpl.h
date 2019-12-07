//
// Created by kecy on 2019/12/5.
//

#ifndef XAPI2_FIRSTAPIIMPL_H
#define XAPI2_FIRSTAPIIMPL_H

#include "../../../include/CrossPlatform.h"
#include "../../../include/FIRSTApi.h"

class FIRSTApiImpl : public FIRSTApi{
public:
    FIRSTApiImpl(const char* libPath);
    ~FIRSTApiImpl();

    void Release() override;

    bool Init() override;

    int Join() override;

    const char *GetTradingDay() override;

    void RegisterFront(char *pszFrontAddress) override;

    void RegisterSpi(FIRSTSpi *pSpi) override;

    void SubscribePrivateTopic(THOST_TE_RESUME_TYPE nResumeType) override;

    void SubscribePublicTopic(THOST_TE_RESUME_TYPE nResumeType) override;

    int ReqAuthenticate(CThostFtdcReqAuthenticateField *pReqAuthenticateField, int nRequestID) override;

    int ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLoginField, int nRequestID) override;

    int ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout, int nRequestID) override;

    int ReqOrderInsert(CThostFtdcInputOrderField *pInputOrder, int nRequestID) override;

    int ReqOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, int nRequestID) override;

    int ReqSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, int nRequestID) override;

    int ReqForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, int nRequestID) override;

    int ReqQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, int nRequestID) override;

    int ReqQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, int nRequestID) override;

    int ReqQryOrder(CThostFtdcQryOrderField *pQryOrder, int nRequestID) override;

    int ReqQryTrade(CThostFtdcQryTradeField *pQryTrade, int nRequestID) override;

    int ReqQryInvestorPosition(CThostFtdcQryInvestorPositionField *pQryInvestorPosition, int nRequestID) override;

    int ReqQryTradingAccount(CThostFtdcQryTradingAccountField *pQryTradingAccount, int nRequestID) override;

    int ReqQryInvestor(CThostFtdcQryInvestorField *pQryInvestor, int nRequestID) override;

    int ReqQryInstrument(CThostFtdcQryInstrumentField *pQryInstrument, int nRequestID) override;

    int ReqQryDepthMarketData(CThostFtdcQryDepthMarketDataField *pQryDepthMarketData, int nRequestID) override;

    int ReqQrySettlementInfo(CThostFtdcQrySettlementInfoField *pQrySettlementInfo, int nRequestID) override;

    int ReqQryInvestorPositionDetail(CThostFtdcQryInvestorPositionDetailField *pQryInvestorPositionDetail,
                                     int nRequestID) override;

    int ReqQrySettlementInfoConfirm(CThostFtdcQrySettlementInfoConfirmField *pQrySettlementInfoConfirm,
                                    int nRequestID) override;

    int ReqQryInvestorPositionCombineDetail(
            CThostFtdcQryInvestorPositionCombineDetailField *pQryInvestorPositionCombineDetail,
            int nRequestID) override;

    int ReqQryForQuote(CThostFtdcQryForQuoteField *pQryForQuote, int nRequestID) override;

    int ReqQryQuote(CThostFtdcQryQuoteField *pQryQuote, int nRequestID) override;

    int SubscribeMarketData(char **ppInstrumentID, int nCount) override;

    int UnSubscribeMarketData(char **ppInstrumentID, int nCount) override;

    int SubscribeForQuoteRsp(char **ppInstrumentID, int nCount) override;

    int UnSubscribeForQuoteRsp(char **ppInstrumentID, int nCount) override;

public:
    static  void* __stdcall OnResponse(char type, void* pApi1, void* pApi2, double double1, double double2, void* ptr1, int size1, void* ptr2, int size2, void* ptr3, int size3);

    void connect(char *pszFrontAddress, CThostFtdcReqAuthenticateField *pReqAuthenticateField,
                 CThostFtdcReqUserLoginField *pReqUserLoginField) override;

private:
    void* _OnResponse(char type, void* pApi1, void* pApi2, double double1, double double2, void* ptr1, int size1, void* ptr2, int size2, void* ptr3, int size3);

    FIRSTSpi* m_pSpi;

    void* m_pLib;
    void* m_pFun;
    void* m_pApi;

    char m_LibPath[1024];
};


#endif //XAPI2_FIRSTAPIIMPL_H
