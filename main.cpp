#include<bits/stdc++.h>
using namespace std;

// Converts key current character into index
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

// trie node
struct TrieNode
{
    struct TrieNode *letters[26];
    int isPresent;
    string meaning;
};

// Returns new trie node (initialized to NULLs)
struct TrieNode *newTrieNode(void)
{
    struct TrieNode *pNode = new TrieNode;
    pNode->isPresent = 0;
    pNode->meaning="";

    for (int i = 0; i < 26; i++)
        pNode->letters[i] = NULL;
    return pNode;
}

// If not present, inserts key into trie.  
void insert(struct TrieNode *root, string str,string meaning)
{
    struct TrieNode *pCrawl = root;

    for (int level = 0; level < str.length(); level++)
    {
        int index = CHAR_TO_INDEX(str[level]);
        if (pCrawl->letters[index]==NULL)
            pCrawl->letters[index] = newTrieNode();

        pCrawl = pCrawl->letters[index];
    }

    // mark last node as leaf and add meaning
    pCrawl->isPresent = 1;
    pCrawl->meaning = meaning;
}

// Returns true if str presents in trie, else false
string search(struct TrieNode *root, string str)
{
    int length = str.length();
    struct TrieNode *pCrawl = root;
    for (int level = 0; level < length; level++)
    {
        int index = CHAR_TO_INDEX(str[level]);

        if (pCrawl->letters[index]==NULL)
            return "None";

        pCrawl = pCrawl->letters[index];
    }

    if (pCrawl != NULL && pCrawl->isPresent)
        return pCrawl->meaning;
    else
        return "None";
}

// Returns 0 if current node has a child
// If all letters are NULL, return 1.
bool isLastNode(struct TrieNode* root)
{
    for (int i = 0; i < 26; i++)
        if (root->letters[i])
            return 0;
    return 1;
}

// Recursive function to print auto-suggestions for given node.
vector<string>suggestions;
void suggestionsRec(struct TrieNode* root, string currPrefix)
{
    // found a string in Trie with the given prefix
    if (root->isPresent)
    {
        suggestions.push_back(currPrefix);
    }

    // All letters struct node pointers are NULL
    if (isLastNode(root))
        return;

    for (int i = 0; i < 26; i++)
    {
        if (root->letters[i])
        {
            currPrefix.push_back(97 + i);
            suggestionsRec(root->letters[i], currPrefix);
            currPrefix.pop_back();
        }
    }
}

// print suggestions for given query prefix.
int printAutoSuggestions(TrieNode* root, string query)
{
    struct TrieNode* pCrawl = root;

    int level;
    int n = query.length();
    for (level = 0; level < n; level++)
    {
        int index = CHAR_TO_INDEX(query[level]);

        // no string in the Trie has this prefix
        if (pCrawl->letters[index]==NULL)
            return 0;

        pCrawl = pCrawl->letters[index];
    }

    // If prefix is last node of tree
    bool isLast = isLastNode(pCrawl);

    // If there are nodes below last node
    if (!isLast)
    {
        string prefix = query;
        suggestionsRec(pCrawl, prefix);
        vector<string>::iterator itr ;
        int j=1;
        for(itr=suggestions.begin();itr!=suggestions.end();itr++)
        {
            cout<<j++<<". "<<*itr<<endl;
        }
        return 1;
    }
}

// Main function
int main()
{
    struct TrieNode* root = newTrieNode();
    insert(root, "quarantine", "a state, period, or place of isolation in which people or animals that have arrived from elsewhere or been exposed to infectious or contagious disease are placed");
    insert(root, "quantum", "a discrete quantity of energy proportional in magnitude to the frequency of the radiation it represents");
    insert(root, "quarrel", " a heated argument or disagreement");
    insert(root, "hammer", "a tool with a heavy metal head mounted at right angles at the end of a handle");
    insert(root, "hamster", "a solitary burrowing rodent with a short tail and large cheek pouches for carrying food");
    insert(root, "hand", "the end part of a person's arm beyond the wrist");
    insert(root, "haze", "a slight obscuration of the lower atmosphere, typically caused by fine suspended particles");
    insert(root, "hair", "any of the fine threadlike strands growing from the skin of humans, mammals, and some other animals");
    insert(root, "cow", "a fully grown female animal of a domesticated breed of ox, kept to produce milk or beef");
    insert(root, "coward", "a person who is contemptibly lacking in the courage to do or endure dangerous or unpleasant things");
    insert(root, "compound", "sympathetic pity and concern for the sufferings or misfortunes of others");
    insert(root, "compassion", "meaning of helping");
    insert(root, "combustion", "the process of burning something");
    vector<string>history;
    
    cout<<"  Welcome to ABC Dictionary\n";
    cout<<"------------------------------\n\n";
    //Loop until user enters "no"
    string ch="no";
    do{
        //Input query
        cout<<"Enter word to search\n";
        string input;
        cin>>input;
        string ans = search(root,input);
        //If query is found
        if(ans!="None")
        {
            history.push_back(input);
            cout<<ans<<endl<<endl;
        }
        
        else
        {
            //Suggestions are being printed
            int comp = printAutoSuggestions(root,input);
            if (comp == 0)
                cout << "No string found with this prefix\n";
            else
            {
                cout<<endl<<input<<" not found..."<<" Above words are a few suggestions\n";
                cout<<"Enter number of word to be searched or press 0 to exit\n";
                int n;
                cin>>n;
                if(n==0)
                    cout<<"Sorry can't find your word\n";
                else
                {
                    string ans=search(root,suggestions[n-1]);
                    history.push_back(suggestions[n-1]);
                    cout<<ans<<endl;
                }
                cout<<endl;
            }
        }
        string his;
        
        cout<<"Do you want to check history?\n";
        cin>>his;
        //Print history if available
        if(his=="yes")
        {
            if(history.size()==0)
                cout<<"\n No history available \n";
            else
            {
                cout<<"\nSEARCH HISTORY:\n";
                for(int i=0;i<history.size();i++)
                {
                    cout<<history[i]<<endl;
                }
            }
        }
        cout<<endl;
     
        //Ask to search another query
        cout<<"Do you want to search other word?\n";
        cin>>ch;
        
    }
    while(ch=="yes");
    
    return 0;
}
