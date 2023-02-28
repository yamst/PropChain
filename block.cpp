#include "block.h"
#include <time.h>
#include "SHA256.h"


block::block(long long nonce, std::string prev_hash, transaction* transactions, int n, bool prealloc):
m_num_transactions(n), m_transactions(transactions), m_accumulative_hash((void*)m_transactions, n*sizeof(transaction)),
m_head(nonce, prev_hash, m_accumulative_hash.getHash()){
    if (n > TX_PER_BLOCK){
        throw too_many_TX();
    }
    if (!prealloc){
        m_transactions = new transaction[TX_PER_BLOCK];
        for (int i = 0 ; i < n ; i++){
            m_transactions[i] = transactions[i];
        }
    }
 

}

block::~block(){
    delete[] m_transactions;
}


block::header::header(long long nonce, std::string prev_hash, std::string root_hash):
m_nonce(nonce), m_previous_hash(prev_hash), m_timestamp(time(NULL)), m_root_hash(root_hash){}
