//
// Created by kan on 11.11.2015.
//

#ifndef BACKTESTER_PNLACTION_H
#define BACKTESTER_PNLACTION_H

#include <list>
#include <vector>

#include "BasisOfStrategy.h"

    struct TDeal {
        TInnerDate OpenTime = 0.0;
        TPrice OpenPrice = GetBadPrice();
        TPrice StopLoss = GetBadPrice();
        TPrice TakeProfit = GetBadPrice();
        TPrice ClosePrice = GetBadPrice();
        TInnerDate CloseTime = 0.0;
        TDealSide DealSide = TDealSide::None;
        size_t Volume = 0;

        TDeal() {
//            Reset();
        }

        TDeal(
            const TInnerDate aOpenTime,
            const TPrice aOpenPrice,
            const TPrice aStopLoss,
            const TPrice aTakeProfit,
            const TPrice aClosePrice,
            const TInnerDate aCloseTime,
            const TDealSide aDealSide,
            const size_t aVolume = 1 ) :
            OpenTime( aOpenTime ),
            OpenPrice( aOpenPrice ),
            StopLoss( aStopLoss ),
            TakeProfit( aTakeProfit ),
            ClosePrice( aClosePrice ),
            CloseTime( aCloseTime ),
            DealSide( aDealSide ),
            Volume( aVolume ){;}

        void Reset() {
            OpenTime = 0.0;
            ResetPrice( OpenPrice );
            ResetPrice( ClosePrice );
            CloseTime = 0.0;
            DealSide = TDealSide::None;
            ResetPrice( StopLoss );
            ResetPrice( TakeProfit );
            Volume = 0;
        }

        bool InAction() const { return DealSide == TDealSide::Buy or DealSide == TDealSide::Sell ; }
    };

    typedef std::list< TDeal > TDeals;
    typedef std::vector< double > TDoubles;
    typedef std::vector< int > TIntegers;
    typedef std::vector< bool > TBools;
    
    TDoubles ToDoublesArray( const TPriceSeries & aPriceSeries );
    
    bool CalcDrawDown(
        const TPriceSeries & aPnL,
        TPrice & aoMaxDD,
        TInnerDate & aoBegin,
        TInnerDate & aoReturn );

    TPrice PnLsToMoneyResult( const TPriceSeries & aPnl );

    TPriceSeries ReductionOfTheIncome(
        const TPriceSeries & aPnL,
        const size_t aProfitNum,
        const double aProfitCoef,
        const size_t aLossNum,
        const double aLossCoef );

    const double gMaxBedAttraction = -99.9;
    const double gFiltredByCount = -33.3;
    const double gFiltredByCountPnl = -66.6;
    const double gFiltredByPnl = 0.0;
    
    const size_t gMinDealsForAllTime = 6;
    
    TPriceSeries DealsToPnLs( const TDeals & aDeals );
    TPrice DealsToPNLCoefficientQuick( const TDeals & aDeals, const TPrice aFirstPrice, const size_t aMinDeals = 10 );
    TPrice DealsToCoeff( const TBarSeries & aBars, const TDeals & aDeals, const size_t aMinDeals, TPrice & aoPnl, TPrice & aoMaxDD, size_t & aoMaxPos, size_t & aoMeadPos );

    TPrice DealsToPNLCoefficient(
        const TDeals & aDeals,
        const TInnerDate aFirstPoint,
        const TInnerDate aLastPoint,
        const TPrice aMinPnl = 0.0,
        const size_t aMinDeals = 10,
        const size_t aQuantTime = 86400 * 7 );
    
    TPriceSeries DealsToDaily( const TPriceSeries & aPnls );
    bool IsGrows( const TPriceSeries & aDailyPnls, const size_t aPeriod, const size_t aTollerance = 1 );

#endif //BACKTESTER_PNLACTION_H