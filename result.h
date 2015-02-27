#ifndef RESULT_H
#define RESULT_H


class Result
{
public:
    double labourCost{0};
    double area{0};
    double materialCost{0};
    double weight{0};
    double finishingCost{0};
    double profitMargin{0};
    double getTotalCost() const {return labourCost + materialCost + finishingCost;}
    double getFinalPrice() const {return getTotalCost() + (getTotalCost() * profitMargin / 100);}
    void complete(bool set) {comp = set;}
    bool complete() const {return comp;}
private:
    bool comp{false};
};

#endif // RESULT_H
