#ifndef MODELS_H
#define MODELS_H

class Model{

    protected:

    float drift;
    float volatility;
    float initialPrice;

    public:

    Model           ();
    Model           (float drift, float volatiliy, float initialPrice);
    Model           (const Model& other);
    Model& operator=(const Model& other);

    public:

    void setDrift       (float drift_       );
    void setVolatility  (float volatility_  );
    void setInitialPrice(float initialPrice_);

    float getDrift       () const;
    float getVolatility  () const;
    float getInitialPrice() const;

    protected:

    /// @brief Computes stochastic derivative at given time t.
    /// @param price_t Price of the stock at time t.
    /// @param t       Time t.
    /// @return Value of derivative.
    virtual float dPrice(float price_t, float delta_t) = 0;
};

#endif