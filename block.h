#ifndef BLOCK_H_
#define BLOCK_H_
#include "sha256.h"
#include "transaction.h"


#define TX_PER_BLOCK 512
#define HASH_BYTES 32



class block{

    public:

    class header{

        public:

        header(long long nonce, std::string prev_hash, std::string root_hash);

        friend block;


        private:

        long long m_nonce;

        std::string m_previous_hash;

        time_t m_timestamp;

        std::string m_root_hash;

    };

    class too_many_TX{};

    // allocated_transactions, if prealloced, should be an array of transactions allocated by new[] 
    block(long long m_nonce, std::string prev_hash, transaction* transactions, int num_of_transactions, bool prealloc = true);

    ~block();

    std::string computeHeaderHash();

    
    private:

    int m_num_transactions;

    transaction* m_transactions;

    SHA256 m_accumulative_hash;

    block::header m_head;

};





#endif /* BLOCK_H_ */