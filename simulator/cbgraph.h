/*
    This file is part of ciberRatoToolsSrc.

    Copyright (C) 2001-2011 Universidade de Aveiro

    ciberRatoToolsSrc is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    ciberRatoToolsSrc is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef CBGRAPH_H
#define CBGRAPH_H

/**
  *@author Nuno Lau, Artur Pereira & Andreia Melo
  */


#include <vector>

using std::vector;

class cbPoint;
class cbNode;
class cbLab;

/**
 * Models the links that start in a given node in the visibilities graph.
 * Each link is characterized by the next node index and by the distance to the next node.
 */
class cbNodeLinks
{
public:
    cbNodeLinks();
    void addLink(int n, double d) { next.push_back(n); dist.push_back(d);}
    int getNext(int l) {return next[l];}
    double getDist(int l) {return dist[l];}
    unsigned int size(void) { return next.size(); }
	void resize(unsigned int size) { next.resize(size);
	                                 dist.resize(size);
                                   }
    //cbNodeLinks & operator=(cbNodeLinks const &other);
private:
    vector<int>     next;
	vector<double>	dist;
};

/**
 * Models a node in the visibilities graph
 */
class cbNode
{
public:
    cbNode(void) {}
    cbNode(cbPoint &p, unsigned int wall,unsigned int corner);
    cbPoint pos(void) { return position; }
    unsigned int wall(void) { return labWall;}
    unsigned int corner(void) { return labCorner;}
private:
    cbPoint position;
	unsigned int labWall,labCorner;
	double dir;
};


/**
 * Models the visibilities graph of a given labirinth
 */
class cbGraph 
{
public:
	void addNode(cbNode node);
	void addInitNode(cbNode node);
	void addFinalNode(unsigned int id, cbNode node);
	void addInitPoint(cbPoint &p);
	void addFinalPoint(unsigned int id, cbPoint &p);
	void addLink(cbNode from,cbNode to, double dist=-1.0);

	/**
	 * the following functions were used as a test for 
	 * optimising the insertion and deletion of initial nodes
	 */
    void setInitState(void){ initStateNodes=nodes.size();
                             for(unsigned int n=0;n<nodes.size();n++)
                                 initStateLinks.push_back(links[n].size());
                           }
    void resetInitState(void) { nodes.resize(initStateNodes);
                                for(unsigned int n=0;n<nodes.size();n++)
                                    links[n].resize(initStateLinks[n]);
                              }

	void buildCornerGraph(void);

	/**
	 * gives the distance from node from to node to
	 */
	double dist(cbNode from, cbNode to);
	double dist(int robId);

    void setLab(cbLab *l) { lab=l;}

	/**
	 * debugging functions
	 */
	void writeNodes(void);
    void writeGraph(void);
    //cbGraph & operator=(cbGraph const &other);

private:
    int findNode(cbNode node);

    void linkToCornerNodes(cbNode node);
    double cornerPathDist(cbNode node1,cbNode node2);

    int nLinks(int init) { return links[init].size(); }
    cbNodeLinks link(int n) { return links[n]; }



	cbLab *lab;

    vector<cbNode>  nodes,   // contains all nodes in the graph
                    inits,   // contains the node linked to the initial positions of robots
                        // is indexed by robot id
                    finals;  // contains the node linked to the final positions of robots
		                // is indexed by robot id
	vector<cbNodeLinks> links; // contains the list of links, the index is the first node
	                           // of the link. Each cbNodeLinks 
                        // contains all links starting from the first node

	unsigned int initStateNodes;
	vector<unsigned int> initStateLinks;
};


#endif
