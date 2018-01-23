#ifndef TT1_CONTEXTGRAPH_DATABASE_H
#define TT1_CONTEXTGRAPH_DATABASE_H

#include <istream>
#include <vector>
#include <map>

#include "vector.h"

class Database
{
public:
    void set_vectors(std::vector<Vector>&& vectors);

    std::vector<Word> most_similar(Word word, size_t topCount);

private:
    std::vector<Vector> m_vectors;
    std::map<std::string, Vector*> m_nameToVec;
};


#endif //TT1_CONTEXTGRAPH_DATABASE_H
