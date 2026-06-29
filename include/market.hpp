#pragma once

struct MarketDataSnapshot
{
    double bestBid = 0.0;
    double bestAsk = 0.0;

    double spread = 0.0;
    double midPrice = 0.0;

    double bidVolume = 0.0;
    double askVolume = 0.0;

    double imbalance = 0.0;

    double bidVWAP = 0.0;
    double askVWAP = 0.0;

    double lastTradePrice = 0.0;
};