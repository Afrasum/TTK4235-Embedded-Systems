static char * TEXT[] = {
    "Vegetarisk kjøttdeig",
    "Tofu",
    "Argentinske villreker",
    "Tilapiafisk",
    "Jeju svart gris",
    "Hanwoo-biff",
    "Wagyu-biff"
};

char * protein(unsigned int degree){
    return TEXT[degree % 7];
}
