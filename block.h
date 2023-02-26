#include "sha256.h"
#include "transaction.h"





class block{

    public:

    class header{};

    block(long long m_nonce, SHA256 prev_hash, transaction** allocated_transactions);

    ~block();

    


    private:


    header m_head;
    transaction* m_transactions;


};

class block::header{

    public:

    header(long long m_nonce, SHA256 prev_hash, )


    private:

    long long m_nonce;
    SHA256 m_previous;
    time_t m_timestamp;
    SHA256 m_root_hash;

};