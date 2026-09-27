
// be sure to change FIRSTNAME and LASTNAME with your own first and last name
#ifndef VALENTINA_RAMIREZSUSARRET_PROJECT2
#define VALENTINA_RAMIREZSUSARRET_PROJECT2

#include <functional>
#include <string>
#include "sha256.h"

// function declarations
std::vector<unsigned int> birthday_attack_1(std::function<unsigned short(unsigned int)> hash_function);
std::vector<unsigned int> birthday_attack_2(std::function<unsigned short(unsigned int)> hash_function);
std::string merkle_commit(const std::vector<std::string>& list, std::function<std::string(std::string)> hash_function);
std::vector<std::pair<std::string,std::string>> merkle_open_position(const std::vector<std::string>& list, std::function<std::string(std::string)> hash_function, const unsigned int i);
int merkle_verify_position(const std::string root, const std::vector<std::pair<std::string, std::string>>& proof, std::function<std::string(std::string)> hash_function, const unsigned int i);
int merkle_verify_full(const std::string root, const std::vector<std::string> list, std::function<std::string(std::string)> hash_function);

// helper functions
std::string merkle_commit2(const std::vector<std::string>& list, std::function<std::string(std::string)> hash_function);
void make_proof(std::vector<std::string> list, unsigned int i, std::vector<std::pair<std::string,std::string>>& proof, std::function<std::string(std::string)> hash_function);


// test functions
int test_bday1();
int test_bday2();
int test_merkle_commit(std::vector<std::vector<std::string>> trees, std::vector<std::string> roots, std::function<std::string(std::string)> hash_function);
int test_merkle_open_position(std::vector<std::vector<std::string>> trees, std::vector<unsigned int> indices, std::vector<std::vector<std::pair<std::string, std::string>>> proofs, std::function<std::string(std::string)> hash_function);
int test_merkle_verify_position(std::vector<std::string> roots, std::vector<std::vector<std::pair<std::string, std::string>>> proofs, std::vector<unsigned int> indices, std::function<std::string(std::string)> hash_function);
int test_merkle_verify_full(std::vector<std::string> roots, std::vector<std::vector<std::string>> trees, std::function<std::string(std::string)> hash_function);

#endif
