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
    const std::vector<Vector>& vectors() const;

    std::vector<WordView> most_similar(WordView word, size_t topCount) const;

private:
    std::vector<Vector> m_vectors;
    std::map<WordView, Vector*> m_nameToVec;
};


#endif //TT1_CONTEXTGRAPH_DATABASE_H
