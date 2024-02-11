// Martins_Prokuratovs_221RDB473
#include "song.cpp"


int main() {
    Song ziemelmeita = Song("Ziemeļmeita", "Jumprava", "Gāju meklēt ziemeļmeitu\nGaru, tālu ceļu veicu", 1988);
    ziemelmeita.sing(1).yell();

    Song prusuZeme = Song(
        "Es izjāju prūšu zemi", 
        "Tauta", 
        "Es izjāju prūšu zemi\nKoklēdamis, spēlēdamis\nEs izjāju prūšu zemi\nKoklēdamis, spēlēdamis\nPrūšu meitas man' gribēja\nPar junkuru paturēti\nPrūšu meitas man' gribēja\nPar junkuru paturēti\nNepalikšu, prūšu meitas\nMan pašami kurzemēi\nNepalikšu, prūšu meitas\nMan pašami kurzemēi\nMan pašami kurzemēi\nSētā jauna līgaviņa"
        , 1001
    );
    prusuZeme.yell();
    
}