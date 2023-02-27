#include "transaction.h"
#include "property.h"


transaction::transaction(int prop_id, int buyer, int seller, int shares):
m_property_id(prop_id), m_buyer(buyer), m_seller(seller), m_shares(shares){}

transaction::transaction():
m_property_id(INVALID_PROPERTY), m_buyer(0), m_seller(0), m_shares(0){}



int transaction::execute(){





}