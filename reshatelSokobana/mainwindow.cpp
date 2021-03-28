#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <string>
#include<utility>
#include "solver.h"
#include <unistd.h>

extern vector<string> read_file(string& filename);
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::load_level(std::string filename)
{
    setk.clear();
    setk.shrink_to_fit();

    level = read_file(filename);
    QVBoxLayout* pole = new QVBoxLayout(this);
    for (std::string str:level)
    {
        QHBoxLayout* line = new QHBoxLayout(this);
        std::vector<QWidget*> _line;
        line->setSpacing(1);
        for(char g:str)
        {
             QWidget* n = new QWidget(this);
             if(g == '#')
                 n->setStyleSheet("background-color: rgb(0, 0, 0);");
             else if(g == '.')
                 n->setStyleSheet("background-color: rgb(255, 255, 255);");
             else if(g == '@' || g=='a')
                 n->setStyleSheet("background-color: rgb(0, 0, 255);");
             else if(g == 'x')
                 n->setStyleSheet("background-color: rgb(255, 0, 0);");
             else if(g == 'o')
                 n->setStyleSheet("background-color:rgb(0, 255, 0);");
             else if(g == '*')
                 n->setStyleSheet("background-color: rgb(170, 0, 255)");
             line->addWidget(n);
             _line.push_back(n);
        }
        setk.push_back(_line);
        pole->addLayout(line);
    }
    pole->setSpacing(1);
    ui->game->setLayout(pole);
}

void MainWindow::pokasji(string& alg)
{
    pair<int,int> koord;
    bool fl = false;
    for(size_t i = 0 ; i < level.size(); i++)
    {
        for(size_t j = 0 ; j < level.at(i).length(); j++)
        {
            if(level.at(i).at(j) == 'a'||
               level.at(i).at(j) == '@' )
            {
                koord = make_pair(i,j);
                fl = true;
            }
        }
        if(fl)
            break;
    }

    for(auto h:alg)
    {
        if(level.at(koord.first).at(koord.second) == '@')
        {
            level.at(koord.first).at(koord.second) = '.';
            setk.at(koord.first).at(koord.second)->setStyleSheet("background-color: rgb(255, 255, 255);");
        }
        else
        {
            level.at(koord.first).at(koord.second) = 'x';
            setk.at(koord.first).at(koord.second)->setStyleSheet("background-color: rgb(255, 0, 0);");
        }

        if(h == 'l')
        {
            if(level.at(koord.first).at(koord.second-1) == 'o')
            {
                if(level.at(koord.first).at(koord.second-2) == 'x')
                {
                    level.at(koord.first).at(koord.second-2) ='*';
                    setk.at(koord.first).at(koord.second-2)->setStyleSheet("background-color: rgb(170, 0, 255);");
                }
                else
                {
                    level.at(koord.first).at(koord.second-2) ='o';
                    setk.at(koord.first).at(koord.second-2)->setStyleSheet("background-color:rgb(0, 255, 0);");
                }
                level.at(koord.first).at(koord.second-1) = '.';
            }

            if(level.at(koord.first).at(koord.second-1) == '*')
            {
                if(level.at(koord.first).at(koord.second-2) == 'x')
                {
                    level.at(koord.first).at(koord.second-2) ='*';
                    setk.at(koord.first).at(koord.second-2)->setStyleSheet("background-color: rgb(170, 0, 255);");
                }
                else
                {
                    level.at(koord.first).at(koord.second-2) ='o';
                    setk.at(koord.first).at(koord.second-2)->setStyleSheet("background-color:rgb(0, 255, 0);");
                }
                level.at(koord.first).at(koord.second-1) = 'x';
            }

            if(level.at(koord.first).at(koord.second-1) == '.')
            {
                setk.at(koord.first).at(koord.second-1)->setStyleSheet("background-color: rgb(0, 0, 255);");
                level.at(koord.first).at(koord.second-1) = '@';
            }

            if(level.at(koord.first).at(koord.second-1) == 'x')
            {
                setk.at(koord.first).at(koord.second-1)->setStyleSheet("background-color: rgb(0, 0, 255);");
                level.at(koord.first).at(koord.second-1) = 'a';
            }

            koord.second--;

        }

        if(h == 'r')
        {
            if(level.at(koord.first).at(koord.second+1) == 'o')
            {
                if(level.at(koord.first).at(koord.second+2) == 'x')
                {
                    level.at(koord.first).at(koord.second+2) ='*';
                    setk.at(koord.first).at(koord.second+2)->setStyleSheet("background-color: rgb(170, 0, 255);");
                }
                else
                {
                    level.at(koord.first).at(koord.second+2) ='o';
                    setk.at(koord.first).at(koord.second+2)->setStyleSheet("background-color:rgb(0, 255, 0);");
                }
                level.at(koord.first).at(koord.second+1) = '.';
            }

            if(level.at(koord.first).at(koord.second+1) == '*')
            {
                if(level.at(koord.first).at(koord.second+2) == 'x')
                {
                    level.at(koord.first).at(koord.second+2) ='*';
                    setk.at(koord.first).at(koord.second+2)->setStyleSheet("background-color: rgb(170, 0, 255);");
                }
                else
                {
                    level.at(koord.first).at(koord.second+2) ='o';
                    setk.at(koord.first).at(koord.second+2)->setStyleSheet("background-color:rgb(0, 255, 0);");
                }
                level.at(koord.first).at(koord.second+1) = 'x';
            }

            if(level.at(koord.first).at(koord.second+1) == '.')
            {
                setk.at(koord.first).at(koord.second+1)->setStyleSheet("background-color: rgb(0, 0, 255);");
                level.at(koord.first).at(koord.second+1) = '@';
            }

            if(level.at(koord.first).at(koord.second+1) == 'x')
            {
                setk.at(koord.first).at(koord.second+1)->setStyleSheet("background-color: rgb(0, 0, 255);");
                level.at(koord.first).at(koord.second+1) = 'a';
            }

            koord.second++;

        }

        if(h == 'u')
        {
            if(level.at(koord.first-1).at(koord.second) == 'o')
            {
                if(level.at(koord.first-2).at(koord.second) == 'x')
                {
                    level.at(koord.first-2).at(koord.second) ='*';
                    setk.at(koord.first-2).at(koord.second)->setStyleSheet("background-color: rgb(170, 0, 255);");
                }
                else
                {
                    level.at(koord.first-2).at(koord.second) ='o';
                    setk.at(koord.first-2).at(koord.second)->setStyleSheet("background-color:rgb(0, 255, 0);");
                }
                level.at(koord.first-1).at(koord.second) = '.';
            }

            if(level.at(koord.first-1).at(koord.second) == '*')
            {
                if(level.at(koord.first-2).at(koord.second) == 'x')
                {
                    level.at(koord.first-2).at(koord.second) ='*';
                    setk.at(koord.first-2).at(koord.second)->setStyleSheet("background-color: rgb(170, 0, 255);");
                }
                else
                {
                    level.at(koord.first-2).at(koord.second) ='o';
                    setk.at(koord.first-2).at(koord.second)->setStyleSheet("background-color:rgb(0, 255, 0);");
                }
                level.at(koord.first-1).at(koord.second) = 'x';
            }

            if(level.at(koord.first-1).at(koord.second) == '.')
            {
                setk.at(koord.first-1).at(koord.second)->setStyleSheet("background-color: rgb(0, 0, 255);");
                level.at(koord.first-1).at(koord.second) = '@';
            }

            if(level.at(koord.first-1).at(koord.second) == 'x')
            {
                setk.at(koord.first-1).at(koord.second)->setStyleSheet("background-color: rgb(0, 0, 255);");
                level.at(koord.first-1).at(koord.second) = 'a';
            }

            koord.first--;

        }

        if(h == 'd')
        {
            if(level.at(koord.first+1).at(koord.second) == 'o')
            {
                if(level.at(koord.first+2).at(koord.second) == 'x')
                {
                    level.at(koord.first+2).at(koord.second) ='*';
                    setk.at(koord.first+2).at(koord.second)->setStyleSheet("background-color: rgb(170, 0, 255);");
                }
                else
                {
                    level.at(koord.first+2).at(koord.second) ='o';
                    setk.at(koord.first+2).at(koord.second)->setStyleSheet("background-color:rgb(0, 255, 0);");
                }
                level.at(koord.first+1).at(koord.second) = '.';
            }

            if(level.at(koord.first+1).at(koord.second) == '*')
            {
                if(level.at(koord.first+2).at(koord.second) == 'x')
                {
                    level.at(koord.first+2).at(koord.second) ='*';
                    setk.at(koord.first+2).at(koord.second)->setStyleSheet("background-color: rgb(170, 0, 255);");
                }
                else
                {
                    level.at(koord.first+2).at(koord.second) ='o';
                    setk.at(koord.first+2).at(koord.second)->setStyleSheet("background-color:rgb(0, 255, 0);");
                }
                level.at(koord.first+1).at(koord.second) = 'x';
            }

            if(level.at(koord.first+1).at(koord.second) == '.')
            {
                setk.at(koord.first+1).at(koord.second)->setStyleSheet("background-color: rgb(0, 0, 255);");
                level.at(koord.first+1).at(koord.second) = '@';
            }

            if(level.at(koord.first+1).at(koord.second) == 'x')
            {
                setk.at(koord.first+1).at(koord.second)->setStyleSheet("background-color: rgb(0, 0, 255);");
                level.at(koord.first+1).at(koord.second) = 'a';
            }

            koord.first++;
        }

        usleep(100000);
    }
}

void MainWindow::on_level1_clicked()
{
    load_level("level1.txt");
}

void MainWindow::on_start_clicked()
{
    solver lev(level);
    string d = lev.reshi_plez_po_bratski();
    pokasji(d);
}

void MainWindow::on_level2_clicked()
{
    load_level("level2.txt");
}

void MainWindow::on_level3_clicked()
{
    load_level("level3.txt");
}
