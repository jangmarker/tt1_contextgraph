#include <algorithm>

#include "database.h"

namespace
{
    using WordSimilarity = std::pair<double, WordView>;

    double similarity(const Vector& lhs, const Vector& rhs) {
        double topSum = 0.0;

        for (int i = 0; i < lhs.values.size(); ++i) {
            topSum += lhs.values[i] * rhs.values[i];
        }

        return topSum / (lhs.euclideanNorm * rhs.euclideanNorm);
    }

    std::vector<WordSimilarity> compare_to_vectors(const Vector& searchVector,
                                                   const std::vector<Vector>& vectors)
    {
        std::vector<WordSimilarity> wordsByIncSim;
        wordsByIncSim.reserve(vectors.size() - 1);

        for (const auto& otherVector : vectors) {
            if (otherVector == searchVector) {
                continue;
            }

            wordsByIncSim.emplace_back(similarity(searchVector, otherVector),
                                       otherVector.word);
        }

        std::sort(wordsByIncSim.begin(), wordsByIncSim.end(),
                  [](const WordSimilarity& lhs, const WordSimilarity& rhs) {
                      return lhs.first < rhs.first;
                  }
        );

        return wordsByIncSim;
    }

    template<typename Container>
    std::vector<WordView> pick_top(const Container& values, std::size_t topCount)
    {
        std::vector<WordView> result;
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

std::vector<WordView> Database::most_similar(WordView word, size_t topCount) const
{
    if (m_nameToVec.find(word) == m_nameToVec.end())
        return {};

    auto searchVector = m_nameToVec.at(word);
    auto wordsByIncSim = compare_to_vectors(*searchVector, m_vectors);
    return pick_top(wordsByIncSim, topCount);
}

const std::vector<Vector>& Database::vectors() const
{
    return m_vectors;
}

