#ifndef PG5501_CONT_EXAM_H23_2001_PLATFORMIO_GENDER_H
#define PG5501_CONT_EXAM_H23_2001_PLATFORMIO_GENDER_H

enum Gender {
    UNKNOWN, FEMALE, MALE
};

static String stringParseGender(Gender gender) {
    switch (gender) {
        case FEMALE: return "Female";
        case MALE: return "Male";
        default: return "Unknown";
    }
}

static Gender genderParseInt(int i) {
    switch (i) {
        case 1: return FEMALE;
        case 2: return MALE;
        default: return UNKNOWN;
    }
}

#endif //PG5501_CONT_EXAM_H23_2001_PLATFORMIO_GENDER_H
