#ifndef MODELS_H
#define MODELS_H

#include <memory>
#include <Model_Data.h>
#include <Jump_Interface.h>

/*
    We attempt to solve some SDE of the form; dX_t = \mu(X_t, t) * dt + \sigm(X_t, t) * dW_t. 
    The functions \mu and \sigma are specifical for each model and define it. 
*/

class Model{

    protected:

    double drift;
    double volatility;
    double initialPrice;
    std::unique_ptr<JumpInterface> jumpModel;

    public:

    Model           ();
    Model           (double drift_, double volatility_, double initialPrice_, std::unique_ptr<JumpInterface> jumpModel_);
    Model           (const ModelData& modelData, std::unique_ptr<JumpInterface> jumpModel_);
    Model           (const Model& other);
    Model& operator=(const Model& other);
    bool  operator==(const Model& other);
    ~Model          () = default;

    public:

    void setDrift       (double drift_                            );
    void setVolatility  (double volatility_                       );
    void setInitialPrice(double initialPrice_                     );
    void setModelData   (const ModelData& modelData_              );
    void setJumpModel   (std::unique_ptr<JumpInterface> jumpModel_);

    double         getDrift       () const;
    double         getVolatility  () const;
    double         getInitialPrice() const;
    JumpInterface* getJumpModel   () const;

    virtual ModelData getModelData() const;

    public:

    /// @brief Computes drift function.
    /// @param price_t Price of the stock at time t.
    /// @param time_t  Given time.
    /// @return Drift at time t.
    virtual double mu(double price_t, double time_t) const = 0;

    /// @brief Computes volatitily function.
    /// @param price_t Price of the stock at time t.
    /// @param time_t  Given time.
    /// @return Volatitily at time t.
    virtual double sigma(double price_t, double time_t) const = 0;
};

#endif