#ifndef VIRTUALPRODUCT_HH
#define VIRTUALPRODUCT_HH
#include <QString>

/**
 * @brief The VirtualProduct class
 * this class is an interface for all the items in the range
 */

class VirtualProduct
{
public:
    virtual void calculate() = 0;
    virtual void createPdf(const QString &name, const QString &phone,
                           const QString &company, const QString &email) = 0;
    virtual ~VirtualProduct() {}
};

#endif // VIRTUALPRODUCT_HH

