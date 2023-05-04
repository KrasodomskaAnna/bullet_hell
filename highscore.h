#pragma once
#include <cstdio>
#include <cstring>
#include "vector.h"
#include "const.h"


struct ScoreBoardItem {
    char username[MAX_PLAYER_NAME_LENGTH];
    int score;
    int level;
};


class Highscore {
public:
    explicit Highscore(const char* path) {
        this->rawFile = fopen(path, "r+");
    }

    void updateHighscore(char* username, int score, int level) {
        char buffer[MAX_PLAYER_NAME_LENGTH + 26];
        sprintf(buffer, "%s %d %d\n", username, score, level);
        fputs(buffer, this->rawFile);
    }

    static int itemCompare(const void* v1, const void* v2) {
        const ScoreBoardItem* p1 = (ScoreBoardItem*)v1;
        const ScoreBoardItem* p2 = (ScoreBoardItem*)v2;
        if (p1->score < p2->score) return -1;
        else if (p1->score > p2->score) return 1;
        else return 0;
    }

    Vector<ScoreBoardItem>* getHighscores() {
        auto* items = new Vector<ScoreBoardItem>();
        while (!feof(this->rawFile)) {
            char line[MAX_PLAYER_NAME_LENGTH + 26]; // 26 poniewaz (space + ew "-" + maxymalna wartosc int'a)*2

            fgets(line, MAX_PLAYER_NAME_LENGTH + 26, this->rawFile);
            auto len = strlen(line);

            ScoreBoardItem item{};

            sscanf(line, "%s %d %d", item.username, &item.score, &item.level);

            items->push_back(item);
        }
        qsort(items->getRawArray(), items->size(), sizeof(ScoreBoardItem), itemCompare);
        return items;
    }

    ~Highscore() {
        fclose(this->rawFile);
    }
private:
    FILE* rawFile;
};
