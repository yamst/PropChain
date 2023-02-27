#ifndef TRANSACTION_H_
#define TRANSACTION_H_
#define FAILED_EXECUTION -1


class transaction{

    public: 

    transaction(int prop_id, int buyer, int seller, int shares);

    transaction(const transaction&);

    transaction(); // invalid spotholder

    ~transaction() = default;

    /* returns the amount needed to be paid or FAILED_EXECUTION if buyer */
    int execute();

    private:

    int m_property_id;
    int m_buyer;
    int m_seller;
    int m_shares;

};

#endif /* TRANSACTION_H_ */