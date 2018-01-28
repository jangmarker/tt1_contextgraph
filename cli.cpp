#include "cli.h"
#include "database.h"
#include "file_access.h"
#include "search.h"
#include "gml_generation.h"

#include "3rdparty/CLI11.hpp"

#include <experimental/filesystem>
#include <string>
#include <string_view>

using namespace std::literals::string_literals;
namespace fs = std::experimental::filesystem;

namespace {
    class Phase {
    public:
        explicit Phase(std::string_view name, std::ostream& ostream)
        : stream(ostream)
        {
            stream << name << "... " << std::flush;
        }

        ~Phase() {
            stream << "Done" << std::endl;
        }

    private:
        std::ostream& stream;
    };
};

int cli(int argc, char** argv, std::ostream& ostream)
{
    CLI::App app{"Text Technologie 1 - Aufgabe 5 - Lösung Jan Marker"};

    static struct {
        std::string databaseFile = "./embeddings/embedding_cbow.vec"s;
        std::string outputFile;
        std::string searchTerm;
        std::size_t neighborCount;
        std::size_t depth;
    } options;

    app.add_option("-i", options.databaseFile, "Path to the vector file.")
            ->check(CLI::ExistingFile)
            ->mandatory(false);
    app.add_option("-o", options.outputFile, "Path to the output GML file.")
            ->mandatory(true);
    app.add_option("-s", options.searchTerm, "Search term.")
            ->mandatory(true);
    app.add_option("-t", options.neighborCount, "Number of neighbors per node.")
            ->mandatory(true);
    app.add_option("-d", options.depth, "Depth of search")
            ->mandatory(true);

    CLI11_PARSE(app, argc, argv);

    Database db;
    {
        Phase phase("Reading file", ostream);
        db = file_access::databaseFrom(fs::path(options.databaseFile));
    }


    search::SearchResultPtr res;
    {
        Phase phase("Searching", ostream);
        res = search::search(db, options.searchTerm,
                             search::NeighborCount(options.neighborCount),
                             search::Depth(options.depth + 1)); // the depth is increased by one to know about
                                                                // connections between leaf nodes and other
                                                                // existing nodes
                                                                // for leaf nodes, the graph generation algorithm
                                                                // will only create edges that point to already
                                                                // existing nodes
    }

    {
        Phase phase("Writing GML", ostream);
        gml_generation::writeToFile(fs::path(options.outputFile), gml_generation::Graph{res, options.depth});
    }

    return 0;
}
