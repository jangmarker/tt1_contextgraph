#include "database.h"

namespace
{
    double similarity(const Vector& lhs, const Vector& rhs) {
        double topSum = 0.0;

        for (int i = 0; i < lhs.values.size(); ++i) {
            topSum = lhs.values[i] * rhs.values[i];
        }

        return topSum / (lhs.euclideanNorm * rhs.euclideanNorm);
    }

    std::multimap<double, Word> compare_to_vectors(const Vector& searchVector,
                                                   const std::vector<Vector>& vectors)
    {
        std::multimap<double, Word> wordsByIncSim;

        for (const auto& otherVector : vectors) {
            if (otherVector == searchVector) {
                continue;
            }

            wordsByIncSim.emplace(similarity(searchVector, otherVector),
                                  otherVector.word);
        }
        return wordsByIncSim;
    }

    template<typename KeyT, typename ValueT>
    std::vector<ValueT> pick_top(const std::multimap<KeyT, ValueT> values, std::size_t topCount)
    {
        std::vector<ValueT> result;
        result.reserve(topCount);
        for (auto cur = values.crbegin();
             topCount > 0 && cur != values.crend();
             --topCount, ++cur) {
            result.push_back(cur->second);
        }
        return result;
    }
}

void Database::set_vectors(std::vector<Vector>&& vectors)
{
    m_vectors = std::move(vectors);
    m_nameToVec.clear();
    for (auto& vector : m_vectors) {
        m_nameToVec.emplace(vector.word, &vector);
    }
}

std::vector<Word> Database::most_similar(Word word, size_t topCount)
{
    if (m_nameToVec.find(word) == m_nameToVec.end())
        return {};

    auto searchVector = m_nameToVec[word];
    auto wordsByIncSim = compare_to_vectors(*searchVector, m_vectors);
    return pick_top(wordsByIncSim, topCount);
}

const std::vector<Vector>& Database::vectors() const
{
    return m_vectors;
}

