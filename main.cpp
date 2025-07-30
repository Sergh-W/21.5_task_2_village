#include <iostream>
#include <vector>
#include <cmath>

enum class RoomType {
    BEDROOM = 1,
    KITCHEN,
    BATHROOM,
    LIVING,
    CHILDREN
};

enum class BuildType {
    HOUSE = 1,
    GARAGE,
    BARN,
    BATH
};

struct Room {
    float square = 0;
    RoomType type = RoomType::BEDROOM;
};

struct Floor {
    float height = 0;
    std::vector<Room> rooms;
};

struct Build {
    BuildType type = BuildType::HOUSE;
    float square = 0;
    std::vector<Floor> floors;
    bool bake = false;
};

struct Plot {
    float square = 0;
    std::vector<Build> build;
    bool building = false;
    int countBuildings = 0;
};

float totalSquare = 0;
int villBuildings = 0;
float totalSqBld = 0;

bool ans (bool &val) {
    std::string answer;
    std::cout << "Enter answer [yes/no]: " << std::endl;
    std::cin >> answer;
    if (answer == "Yes" || answer == "Y" || answer == "y" || answer == "yes") return true;
    else return false;
}

Build buildHouse(){
    int countFloor = 1;
    Build build;
    Floor floor;

    std::cout << "Add bake to house? " << std::endl;
    ans(build.bake);

    do {
        std::cout << "How many floors (1-3)?: " << std::endl;
        std::cin >> countFloor;
    } while (countFloor < 1 || countFloor > 3);

    for (int i = 0; i < countFloor; ++i) {

        int countRoom = 0;

        do {
            std::cout << "How many rooms (2-4) on the " << i + 1 << " floor: " << std::endl;
            std::cin >> countRoom;
        } while (countRoom < 2 || countRoom > 4);

        do {
            std::cout << "Enter height floor: " << std::endl;
            std::cin >> floor.height;
        } while (floor.height < 1);

        for (int j = 0; j < countRoom; ++j) {
            Room room;
            int type = 0;

            do {
                std::cout << "Enter room type (BEDROOM = 1, KITCHEN = 2, BATHROOM = 3, LIVING = 4, CHILDREN = 5): " << std::endl;
                std::cin >> type;
            } while (type < 1 || type > 5);

            do {
                std::cout << "Enter room square: " << std::endl;
                std::cin >> room.square;
            } while (room.square < 1);

            room.type = static_cast<RoomType>(type);

            floor.rooms.push_back(room);

            if (i == 1) totalSqBld += room.square;
        }

        build.floors.push_back(floor);
    }

    return build;
}

Build buildGarage() {
    Build build;
    build.type = BuildType::GARAGE;

    do {
        std::cout << "Enter square garage: " << std::endl;
        std::cin >> build.square;
    } while (build.square < 1);
    totalSqBld += build.square;
    return build;
}

Build buildBarn() {
    Build build;
    build.type = BuildType::BARN;

    do {
        std::cout << "Enter square barn: " << std::endl;
        std::cin >> build.square;
    } while (build.square < 1);
    totalSqBld += build.square;
    return build;
}

Build buildBath() {
    Build build;
    build.type = BuildType::BATH;

    do {
        std::cout << "Enter square bath: " << std::endl;
        std::cin >> build.square;
    } while (build.square < 1);
    totalSqBld += build.square;
    std::cout << "Add bake to bath? " << std::endl;
    ans(build.bake);

    return build;
}

Plot fillPlot() {
    Plot plot;
    int count = 0;

    do {
        std::cout << "Enter square plot: " << std::endl;
        std::cin >> plot.square;
    } while (plot.square < 1);

    totalSquare += plot.square;

    // House
    do {
        std::cout << "How many houses are on the plot? " << std::endl;
        std::cin >> count;
    } while (count < 1);

    plot.countBuildings += count;

    for (int i = 0; i < count; ++i) {
        plot.build.push_back(buildHouse());
    }

    // Garage
    std::cout << "Is there a garage on the plot?" << std::endl;
    if (ans(plot.building)) {
        plot.build.push_back(buildGarage());
        plot.countBuildings ++;
    }

    // Barn
    std::cout << "Is there a barn on the plot?" << std::endl;
    if (ans(plot.building)) {
        plot.build.push_back(buildBarn());
        plot.countBuildings ++;
    }

    // Bath
    std::cout << "Is there a bath on the plot?" << std::endl;
    if (ans(plot.building)) {
        plot.build.push_back(buildBath());
        plot.countBuildings ++;
    }

    std::cout << "Buildings = " << plot.countBuildings << std::endl;
    std::cout <<std::endl;
    villBuildings += plot.countBuildings;

    return plot;
}

int main()
{
    int countPlots = 0;
    std::vector <Plot> plots;

    do {
        std::cout << "How many plots are there in the village ? " << std::endl;
        std::cin >> countPlots;
    } while (countPlots < 1);

    for (int i = 0; i < countPlots; ++i) {
        std::cout << "Plot # " << i + 1 << std::endl;
        plots.push_back(fillPlot());
    }

    std::cout << "Total area of plots in the village = " << totalSquare << " m^2" << std::endl;
    std::cout << "Total square of buildings in the village = " << totalSqBld << " m^2" << std::endl;
    std::cout << "Total number of buildings in the village = " << villBuildings << std::endl;
    std::cout << "Buildings occupy " << std::ceil((totalSqBld * 100) / totalSquare) << " % of the entire area of the village." << std::endl;

    return 0;
}
