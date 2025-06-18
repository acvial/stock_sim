#ifndef MODELS_H
#define MODELS_H

/*
    We attempt to solve some SDE of the form; dX_t = \mu(X_t, t) * dt + \sigm(X_t, t) * dW_t. 
    The functions \mu and \sigma are specifical for each model and define it. 
*/

struct ModelData{

    ModelData() = default;
    ModelData(double drift_, double volatility_, double initialPrice_){
        drift        = drift_;
        volatility   = volatility_;
        initialPrice = initialPrice_;
    }
    ~ModelData() = default;

    double drift;
    double volatility;
    double initialPrice;
};

class Model{

    protected:

    double drift;
    double volatility;
    double initialPrice;

    public:

    Model           ();
    Model           (double drift_, double volatility_, double initialPrice_);
    Model           (const ModelData& modelData);
    Model           (const Model& other);
    Model& operator=(const Model& other);
    ~Model          () = default;

    public:

    void setDrift       (double drift_       );
    void setVolatility  (double volatility_  );
    void setInitialPrice(double initialPrice_);

    double getDrift       () const;
    double getVolatility  () const;
    double getInitialPrice() const;

    protected:

    /// @brief Computes drift function.
    /// @param price_t Price of the stock at time t.
    /// @param time_t  Given time.
    /// @return Drift at time t.
    virtual double mu(double price_t, double time_t) = 0;

    /// @brief Computes volatitily function.
    /// @param price_t Price of the stock at time t.
    /// @param time_t  Given time.
    /// @return Volatitily at time t.
    virtual double sigma(double price_t, double time_t) = 0;
};

#endif