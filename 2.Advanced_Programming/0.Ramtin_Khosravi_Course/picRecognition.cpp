//mashhad ferdowsi ui contest:recognition of letters in given picture and then checking if words given can be created with those letters
#include <iostream>
using namespace std;

int main()
{
    int occured[12] = {};

    int row, col, q; cin >> row >> col >> q;
    char paper[row][col];
    for(int r=0; r<row; r++)
    {
        for(int c=0; c<col; c++)
        {
            cin >> paper[r][c]; 
        }
    }
    int tr=0, tc =0;
    for(int r=0; r<row; r++)
    {
        for(int c=0; c<col; c++)
        {
            if(paper[r][c] != '.')
            {
                switch(paper[r][c])
                {
                    case 'A':
                    {
                        if(c>=1 && c+2<col && r+4<row)
                        {
                            if(paper[r][c+1] == 'A' && paper[r+1][c+2] == 'A' && paper[r+1][c-1] == 'A' && paper[r+2][c-1] == 'A' && paper[r+2][c] == 'A' && paper[r+2][c+1] == 'A' && paper[r+2][c+2] == 'A' && paper[r+3][c-1] == 'A' && paper[r+3][c+2] == 'A' && paper[r+4][c-1] == 'A' && paper[r+4][c+2] == 'A')
                                occured['A'-'A']++;
                        }
                        break;
                    }
                    case 'B':
                    {
                        if(c+3<col && r+4<row)
                        {
                            if(paper[r][c+1] == 'B' && paper[r][c+2] == 'B' && paper[r+1][c] == 'B' && paper[r+1][c+3] == 'B' && paper[r+2][c] == 'B' && paper[r+2][c+1] == 'B' && paper[r+2][c+2] == 'B' && paper[r+3][c] == 'B' && paper[r+3][c+3] == 'B' && paper[r+4][c] == 'B' && paper[r+4][c+1] == 'B' && paper[r+4][c+2] == 'B')
                                occured['B'-'A']++;
                        }
                        break;
                    }
                    case 'C':
                    {
                        if(r+4<row && c+2<col)
                        {
                            if(paper[r][c+1]=='C' && paper[r][c+2]=='C' && paper[r+1][c-1]=='C' && paper[r+2][c-1]=='C' && paper[r+3][c-1]=='C' && paper[r+4][c]=='C' && paper[r+4][c+1]=='C' && paper[r+4][c+2]=='C')
                                occured['C'-'A']++;
                        }
                        break;
                    }
                    case 'D':
                    {
                        if(r+4<row && c+3<col)
                            if(paper[r][c+1]=='D' && paper[r][c+2]=='D' && paper[r+1][c]=='D' && paper[r+1][c+3]=='D' && paper[r+2][c]=='D' && paper[r+2][c+3]=='D' && paper[r+3][c]=='D' && paper[r+3][c+3]=='D' && paper[r+4][c]=='D' && paper[r+4][c+1]=='D' && paper[r+4][c+2]=='D') 
                                occured['D'-'A']++;
                        break;
                    }
                    case 'E':
                    {
                        if(c+3<col && r+4<row)
                        {
                            tr =r; tc =c;
                            for(int k=1; k<=3; k++)
                            {
                                tc++;
                                if(paper[tr][tc] != 'E')
                                    break;
                            }
                            tc-=3;tr++;
                            if(paper[tr][tc] != 'E')
                                break;
                            tr++;
                            for(int k=0; k<2; k++)
                            {
                                tc++;
                                if(paper[tr][tc] != 'E')
                                    break;
                            }
                            tc-=2;tr++;
                            if(paper[tr][tc] != 'E')
                                    break;
                            tr++;
                            for(int k=0; k<3; k++)
                            {
                                tc++;
                                if(paper[tr][tc] != 'E')
                                    break;
                            }

                            occured['E'-'A']++;
                        }      
                        break;
                    }
                    case 'F':
                    {
                        if(r+4<row && c+3<col)
                        {
                            tr=r; tc=c;
                            for(int k=0; k<3; k++)
                            {
                                tc++;
                                if(paper[tr][tc] != 'F')
                                    break;
                            }
                            tc-=3; tr++;
                            if(paper[tr][tc] != 'F')
                                    break;
                            tr++;
                            for(int k=0; k<2; k++)
                            {
                                tc++;
                                if(paper[tr][tc] != 'F')
                                    break;
                            }
                            tc-=2; tr++;
                            if(paper[tr][tc] != 'F')
                                    break;
                            tr++;
                            if(paper[tr][tc] != 'F')
                                    break;

                            occured['F'-'A']++;
                        }
                        break;
                    }
                    case 'G':
                    {
                        if(r+4<row && c+2<col && c-1>=0)
                        {
                            tr=r; tc=c;
                            for(int k=0; k<2; k++)
                            {
                                tc++;
                                if(paper[tr][tc] != 'G')
                                    break;
                            tc-=3; tr++;
                            if(paper[tr][tc] != 'G')
                                    break;
                            tr++;
                            if(paper[tr][tc] != 'G')
                                    break;
                            tc+=2;
                            if(paper[tr][tc] != 'G')
                                    break;
                            tc++;
                            if(paper[tr][tc] != 'G')
                                    break;
                            tc-=3; tr++;
                            if(paper[tr][tc] != 'G')
                                    break;
                            tc+=3;
                            if(paper[tr][tc] != 'G')
                                    break;
                            tc-=2; tr++;
                            for(int k=0; k<2; k++)
                            {
                                tc++;
                                if(paper[tr][tc] != 'G')
                                    break;
                            }

                            occured['G'-'A']++;
                        }
                        break;
                        }
                    }
                    case 'H':
                    {
                        if(c+3<col && r+4<row)
                        {
                            tr=r; tc=c;
                            for(int k=0; k<4; k++)
                            {
                                tr++;
                                if(paper[tr][tc] != 'H')
                                    break;
                            }
                            tr-=4;tc+=3;
                            for(int k=0; k<4; k++)
                            {
                                tr++;
                                if(paper[tr][tc] != 'H')
                                    break;
                            }
                            tr-=2;tc--;
                            if(paper[tr][tc] != 'H')
                                    break;
                            tc--;
                            if(paper[tr][tc] != 'H')
                                    break;
                                
                            occured['H'-'A']++;
                        }
                        break;
                    }
                    case 'I':
                    {
                        if(r+4<row)
                        {
                            tr=r;tc=c;
                            for(int k=0; k<4; k++)
                            {
                                tr++;
                                if(paper[tr][tc] != 'I')
                                    break;
                            }
                            occured['I'-'A']++;
                        }
                        break;
                    }
                    case 'J':
                    {
                        if(r+4<row && c-3>=0)
                        {
                            tr=r;tc=c;
                            for(int k=0; k<3; k++)
                            {
                                tr++;
                                if(paper[tr][tc] != 'J')
                                    break;
                            }
                            tc-=3;
                            if(paper[tr][tc] != 'J')
                                    break;
                            tr++;tc++;
                            if(paper[tr][tc] != 'J')
                                    break;
                            tc++; 
                            if(paper[tr][tc] != 'J')
                                    break;
                            
                            occured['J'-'A']++;
                        }
                        break;
                    }
                    case 'K':
                    {
                        if(r+4<row && c+3<col)
                        {
                            tr=r; tc=c;
                            for(int k=0; k<4; k++)
                            {
                                tr++;
                                if(paper[tr][tc] != 'K')
                                    break;
                            }
                            tr-=4;tc+=3;
                            if(paper[tr][tc] != 'K')
                                    break;
                            tr++; tc--;
                            if(paper[tr][tc] != 'K')
                                    break;
                            tr++; tc--;
                            if(paper[tr][tc] != 'K')
                                    break;
                            tr++; tc++;
                            if(paper[tr][tc] != 'K')
                                    break;
                            tr++; tc++;
                            if(paper[tr][tc] != 'K')
                                    break;

                            occured['K'-'A']++;
                        }
                        break;
                    }
                    case 'L':
                    {
                        if(r+4<row && c+2<col)
                        {
                            tr=r;tc=c;
                            for(int k=0; k<4; k++)
                            {
                                tr++;
                                if(paper[tr][tc] != 'L')
                                    break;
                            }
                            for(int k=0; k<2; k++)
                            {
                                tc++;
                                if(paper[tr][tc] != 'K')
                                    break;
                            }
                            occured['L'-'A']++;
                        }
                        break;
                    }

                }

            }
        }
    }

    string suspect;
    int counter=0;
    for(int i=0; i<q; i++)
    {
        int occured2[12]={};
        cin >> suspect;
        for(int j=0; j<suspect.length(); j++)
        {
            occured2[suspect[j]-'A']++;
        }

        bool flag = true;
        for(int j=0; j<12; j++)
        {
            if(occured[j] < occured2[j])
            {
                flag = false;
                break;
            }
        }
        if(flag)
            counter++;
    }
    cout << counter;

    return 0;
    
}
