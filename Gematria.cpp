#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

/**
 * Returns the count of the number of vowels (including y).
 * Note: It must handle both upper- and lower-case.
 *
 * @param word the word whose vowels need counting.
 *
 * @return the count of the number of vowels (including y).
 */
int vowel_count(string word) {
    // TODO: insert your implementation
    int vowel = 0;
    for(int i=0; word[i]!='\0'; ++i)
    {
        if(word[i]=='a' || word[i]=='e' || word[i]=='i' || word[i]=='o' || word[i]=='u' || word[i] == 'y' ||
           word[i]=='A' || word[i]=='E' || word[i]=='I' || word[i]=='O' || word[i]=='U' || word[i] == 'Y')
           ++vowel;
    }
return vowel;
}

/**
 * Returns the number of syllables in a word.
 * To make this simple, use the following rules:
 *    Each group of adjacent vowels (a, e, i, o, u, y)
 *    counts as one syllable
 *    (for example, the “ea” in “real” contributes one syllable,
 *    but the “e ... a” in “regal” counts as two syllables).
 *    However, an “e” at the end of a word doesn’t count as a
 *    syllable. Also each word has at least one syllable,
 *    even if the previous rules give a count of 0.
 *
 * For example:
 *    syllable_count("Harry") returns 2
 *    syllable_count("hairy") returns 2
 *    syllable_count("hare")  returns 1
 *    syllable_count("the")   returns 1
 *
 * @param word the word whose syllables to count
 *
 * @return the number of syllables in a word.
 */
int syllable_count(string word) {
// TODO: insert your implementation
    int syllable_count = 0;

    for (int i=0; i < word.size()-1; i++) {
        string current;
        string next;
        current = word.substr(i, 1);
        next =  word.substr(i+1, 1);
        if (vowel_count(current)) {
           if (vowel_count(next)) {
           syllable_count++;
           i++; }
           else {
           syllable_count++; }
       }
    }
return syllable_count;
}

/**
 * Given a file that contains 1 word per line, returns
 * a vector of all the words that have min <= length <= max.
 *
 * @param filename name of a file with 1 word per line.
 * @param min the min length (inclusive).
 * @param max the max lenght (inclusive).
 *
 * @return a vector of all the words that have min <= length <= max,
 *         if none match, an empty vector is returned.
 */

vector<string> filter_dict(string filename, int min, int max) {
    // TODO: insert your implementation
    fstream data(filename);
    vector<string> filter_dict;

    while(getline(data, filename)) {
        if (sizeof(filename) >= min && sizeof(filename) <= max) {
            filter_dict.push_back(filename);
        }
    }
return filter_dict;
}


class GematricString {
private:
    /**
     * The original word (case-preserved)
     */
    string word;
public:
    /**
     * Creates a GematricString object.
     * @param the_word the word to be stored (preserving its case).
     */
    // TODO: implement this
    GematricString(string the_word) :
        word(the_word) {
    }
    /**
     * Returns the word.
     * @return the word
     */
    // TODO: implement this
    string get_word() const {
        return word;
    }

    /**
     * Returns the gematric value of the string.
     * "Gematria is the act of assigning numeric values
     * to letters in an alphabet." -- taken from
     * https://en.wikipedia.org/wiki/Gematria, last access Oct 13, 2016
     * It is believed that words or phrases that have
     * equal gematric values are related.
     *
     * The gematric value of a word is the sum of the
     * values of all the letters in the word such that
     * a = 1, b = 2, c = 3, ..., y = 25, z = 26, irrespective of case.
     * For non-letters, the gematric value is 0.
     * For example, "Phil" has a value of P=16 + h=8 + i=9 + l=12 == 45.
     *
     * @return the gematric value of the GematricString.
     */
    // TODO: implement this: int gematric_value(string str) const;
    int gematric_value() const{
        int sum = 0;
        string str;
        for(int i; i < str.size(); i++){
            if(str[i]<91 && str[i]> 64){
                sum += (str[i]-64);
            }
            else if(str[i]<123 && str[i]> 96){
                sum += (str[i]-96);
            }
        }
        return sum;
    }
};

/**
 * Loads each word in the file into a GematricString object
 * putting each object into a vector and returning that.
 *
 * @param filename the name of the file containing 1 word per line.
 * @return a vector of GematricStrings 1 for each word in the given file.
 */

// TODO: insert your implementation
vector<GematricString> load_words(string filename) {
    vector<GematricString> GSLoad;
    fstream data(filename);
    if (data.is_open()) {
        string line;
        while (getline(data, line)) {
            GematricString *pgs = new GematricString(line);
            GSLoad.push_back(*pgs);
        }
    }
    return GSLoad;
}

/**
 * Returns a vector of strings that have the same gematric value
 * as the given word.
 *
 * @param word_to_match the word to match.
 * @param gem_words a vector of GematricStrings that will be searched for
 *                  words that have the same gematric value as word_to_match.
 * @return a vector of strings that have the same gematric value
 *         as the given word, if none match an empty vector is returned.
 */
vector<string> gematria(string word_to_match, vector<GematricString> gem_words) {
    vector<string> GSList;
    GematricString wordToMatch(word_to_match);

    int gem_value = wordToMatch.gematric_value();
    for (GematricString gs : gem_words) {
        if (gem_value == gs.gematric_value()) {
            GSList.push_back(gs.get_word());
        }
    }
    return GSList;
}

int main() {

    //Mock Input for file input
    string filename;
    fstream infile {filename};

    //Vowel Test
    cout << "There are " << vowel_count("Data Structures") << " vowels in the string 'Data Structures'" << endl;
    //Syllable Test
    cout << "There are " << syllable_count("Data Structures") << " syllables in the words 'Data Structures'" << endl;
    //Gematric Value Test
    GematricString test("Structures");
    cout << "The gematric value of the word Structures is " << test.gematric_value() << endl;

    const vector<GematricString>
    &testVector = load_words(filename);
    for (int i=0; i < testVector.size(); i++) {
        cout << testVector[i].get_word() << endl;
    }

    const vector<string>
    &GVector = gematria("Data Structures", mockVector);
    int counter = 0;
    for (int i = 0; i < GVector.size(); i++) {
        cout << GVector[i] << endl;
        if (counter == 20) {
            break;
        }
        counter++;
    }
return 0;
}
