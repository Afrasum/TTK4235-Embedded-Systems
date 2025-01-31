static char * TEXT[] = {
    "Coop Tex Mex Taco Mild Sauce",
    "First Price Tacosaus",
    "Broken Taco Almost Illegal Salsa",
    "Broken Taco Supreme Tacotopping",
    "Heinz Ketchup",
    "Tine Rømme",
    "Huy Fong Sriracha"
};


char * taco_saus(unsigned int degree){
    return TEXT[degree % 7];
}
