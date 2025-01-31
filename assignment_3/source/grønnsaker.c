static char * TEXT[] = {
    "Løk + Mais",
    "Cherrytomater + Avokado",
    "Ananas + Nacho",
    "Sørlandschips Spansk Paprika",
    "Gruyere-ost + Mango",
    "Chilibønner"
};

char * gronnsaker(unsigned int degree){
    return TEXT[degree % 6];
}
