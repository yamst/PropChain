#include "property.h"


property::property(int prop_id, std::string city, std::string street, int house_num, int shares, double total_value,
int* owners, int num_of_tenants, int* tenants, Metadata addit_info):
m_property_id(prop_id), m_city(city), m_street(street), m_house_number(house_num), m_shares(shares),
m_total_value(total_value), m_owners(NULL), m_number_of_tenants(num_of_tenants), m_tenants(NULL), m_info(addit_info)
    {
        m_owners = new int[shares];
        m_tenants = new int[num_of_tenants];
        for (int i = 0 ; i < shares ; i++){
            m_owners[i] = owners[i];
        }
        for (int i = 0 ; i < num_of_tenants ; i++){
            m_tenants[i] = tenants[i];
        }
    }

property::~property(){
    delete[] m_owners;
    delete[] m_tenants;
}

void property::splitshares(int splitting_constant){

    int* new_owners = new int[splitting_constant*(this -> m_shares)];
    
    for (int i = 0 ; i < (this -> m_shares) ; i++){
        for (int j = 0 ; j < splitting_constant ; j++){
            new_owners[(splitting_constant)*i +j] = (this -> m_owners)[i];
        }
    }
    delete[] (this -> m_owners);
    this -> m_owners = new_owners;
    this -> m_shares = (this -> m_shares) * splitting_constant;
    
}