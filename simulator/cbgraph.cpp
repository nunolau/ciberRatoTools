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

#include "cbpoint.h"
#include "cblab.h"
#include "cbrobot.h"
#include "cbgraph.h"

// cNodebLinks

#ifndef MicWindows

#include <values.h>

#else

#ifndef MAXFLOAT
#define MAXFLOAT (1e30)
#endif
#ifndef MAXINT
#define MAXINT (0x7fffffff)
#endif

#endif


#include <algorithm>
#include <assert.h>

cbNodeLinks::cbNodeLinks() 
{}

/*
cbNodeLinks & cbNodeLinks::operator=(cbNodeLinks const &other)
{
//	if(this != &other) {
	    next=other.next;
	    dist=other.dist;
//	}

	return *this;
}
*/

// cbNode

cbNode::cbNode(cbPoint &p, unsigned int wall, unsigned int corner)
{
    position=p;
    labWall=wall;
    labCorner=corner;
}

// cbGraph

/*
cbGraph &cbGraph::operator=(cbGraph const &other)
{
       
//	if(this != &other) {
	    lab=other.lab;

	    nodes=other.nodes;   
	    inits=other.inits;  

	    finals=other.finals; 

	    links=other.links; 

	    initStateNodes=other.initStateNodes;
	    initStateLinks=other.initStateLinks;
//	}

	return *this;
}
*/

void cbGraph::addNode(cbNode node)
{
    cbNodeLinks empty;

    nodes.push_back(node);
    links.push_back(empty);
}

/*!
 * Adds a node to list of initial nodes.
 * Order of invocation determines the id of these initial nodes
 */
void cbGraph::addInitNode(cbNode node)
{
	addNode(node);
	inits.push_back(node);
}

/*!
 * Adds a node to list of final nodes.
 * Order of invocation is not relevant. 
 */
void cbGraph::addFinalNode(unsigned int id,cbNode node)
{
	if(id==0) assert(0);
	addNode(node);
	if(finals.size()<id) finals.resize(id);
	finals[id-1]=node;
}

/*!
 * Adds a link from node from to node to with distance dist.
 */
void cbGraph::addLink(cbNode from, cbNode to, double dist)
{
    int f,t;

    f=findNode(from);
    if(f==-1) {
//       fprintf(stderr,"adding node from x=%f y=%f\n", from.pos().X(),from.pos().Y());
       addNode(from);
       f=nodes.size()-1;
    }

    t=findNode(to);
    if(t==-1) {
//       fprintf(stderr,"adding node to x=%f y=%f\n", to.pos().X(),to.pos().Y());
       addNode(to);
       t=nodes.size()-1;
    }

//    fprintf(stderr,"addLink %2d(%6.3f,%6.3f)->%2d(%6.3f,%6.3f) = %6.3f\n", 
//		        f,from.pos().X(),from.pos().Y(),
//		        t,to.pos().X(),to.pos().Y(),
//			dist);
    links[f].addLink(t,dist);
}

/*!
 * Determines the distance from robId initial point  to robId final point
 */
double cbGraph::dist(int robId)
{
	return dist(inits[robId-1],finals[robId-1]);
}

/*!
 * Determines the distance from node from to node to
 * Both nodes must be in the graph before invocation.
 */
double cbGraph::dist(cbNode from, cbNode to)
{
    vector <double> distMinToNode(nodes.size());
    vector <int> toFollow;
    double distMin,distMinToFollow, distNode;
    //cbNode curNode;
    int nodeToFollow, indToFollow, l, t, aux, destNode;
    unsigned int n;
    bool there;

//    fprintf(stderr,"dist from i(%6.3f,%6.3f) -> f(%6.3f,%6.3f)\n",
//		    from.pos().X(),from.pos().Y(),
//		    to.pos().X(),to.pos().Y());

    //DEBUG
    //FILE *fdebug=fopen("graphbuild.txt","w");
    //int count=0;

    for(n=0;n<nodes.size();n++)
       distMinToNode[n]=MAXFLOAT;

    aux=findNode(from);
    if(aux==-1) { 
	   fprintf(stderr,"cbgraph::dist could not find node at %.2f,%.2f\n", from.pos().X(), from.pos().Y());
           assert(0);
    }

    toFollow.push_back(aux);
    distMinToNode[aux]=0;

    t=findNode(to);
    if(t==-1) assert(0);

    if(nodes[t].pos() == nodes[aux].pos()) return 0.0;

    distMin=MAXFLOAT;
    distMinToFollow=MAXFLOAT;
    there=false;
    while(toFollow.size()>0 && (!there || distMinToFollow < distMin)) {
        // choose nodeToFollow from toFollow list
        nodeToFollow = toFollow[0];
	indToFollow=0;
	distMinToFollow=distMinToNode[nodeToFollow];
        for(n=1;n<toFollow.size();n++) {
	    if(distMinToNode[toFollow[n]] < distMinToFollow) {
		nodeToFollow=toFollow[n];
	        distMinToFollow =  distMinToNode[nodeToFollow];
		indToFollow=n;
	    }
	}
	// search links of nodeToFollow 
	//curNode=nodes[nodeToFollow];
	distNode=distMinToNode[nodeToFollow];
	for(l=0;l<nLinks(nodeToFollow);l++) {

	    destNode=link(nodeToFollow).getNext(l);

	    if(distNode+link(nodeToFollow).getDist(l) < distMinToNode[destNode]) {

	        distMinToNode[destNode]=distNode+link(nodeToFollow).getDist(l);

                if(std::find(toFollow.begin(),toFollow.end(),destNode)==toFollow.end())
		    toFollow.push_back(destNode);

	        if(destNode==t) {
		   there=true;
		   distMin=distMinToNode[destNode];
		}
            }
	}
	toFollow.erase(toFollow.begin()+indToFollow);

// DEBUG
/**
        for(n=0;n<nodes.size();n++)
		fprintf(fdebug,"%7d",n);
	fprintf(fdebug,"\n");
        for(n=0;n<nodes.size();n++)
		if(distMinToNode[n]<MAXFLOAT)
                    fprintf(fdebug,"%7.2f",distMinToNode[n]);
		else
                    fprintf(fdebug,"%7s","MAX");;
	fprintf(fdebug,"\n");
        for(n=0;n<nodes.size();n++)
            if(std::find(toFollow.begin(),toFollow.end(),n)!=toFollow.end())
                    fprintf(fdebug,"%7s","Follow");
	   else     fprintf(fdebug,"%7s","");
	fprintf(fdebug,"\n\n");
        fflush(fdebug);
        count++;
        if(count==50) exit(1);
**/
	

    }

    // DEBUG
    //fprintf(fdebug,"dist = %6.3f\n",distMin);
    //fclose(fdebug);

    return distMin;
}

int cbGraph::findNode(cbNode node)
{
    unsigned int n;

    for(n=0;n<nodes.size();n++)
        if(node.pos()==nodes[n].pos()) return n;
    return -1;
}

/*! 
 * Builds the graph of visibilities for the current labyrinth.
 */
void cbGraph::buildCornerGraph(void)
{
    unsigned int wi,wf,ci,cf;
    unsigned int n1,n2;
    double dist;
    cbPoint posi,posf;

    assert(lab!=0);

    // graph nodes are positioned at the distance of the 
    // robot radius with respect to some corner
    // The same corner may have several nodes (with diferrent
    // angles with respect to the corner)

    for(wi = 0; wi < lab->nWalls(); wi++) {
        
        vector<cbPoint> &corneri = lab->Wall(wi)->Corners();

        for(ci = 0; ci < corneri.size(); ci++) {
//           fprintf(stderr,"wi=%d ci=%d convex=%d\n",
//			   wi,ci,lab->Wall(wi)->convexCorner(ci));

	   if( ! lab->Wall(wi)->convexCorner(ci)) continue;

           for(wf = 0; wf < lab->nWalls(); wf++) {

               vector<cbPoint> &cornerf = lab->Wall(wf)->Corners();

               for(cf = 0; cf < cornerf.size(); cf++) {

//                   fprintf(stderr,"wf=%d cf=%d convex=%d\n",
//			   wf,cf,lab->Wall(wf)->convexCorner(cf));

		   if(wf==wi && cf==ci) continue;
	           if( ! lab->Wall(wf)->convexCorner(cf)) continue;

		   //if(lab->Wall[wi]->possibleDirection())
	           posi=corneri[ci]+(cornerf[cf]-corneri[ci]).normalize().rotate(M_PI/2)*ROBOT_RADIUS;
	           posf=cornerf[cf]+(cornerf[cf]-corneri[ci]).normalize().rotate(M_PI/2)*ROBOT_RADIUS;

	//	   fprintf(stderr,"testing 1 posi(%f,%f) posf(%f,%f)\n",
	//			       posi.X(),posi.Y(),
	//			       posf.X(),posf.Y());
                   if( lab->reachableRobot(posi, posf) ) {
	               dist=posi.distance(posf);
	       
//		       fprintf(stderr,"1 posi(%f,%f) posf(%f,%f)\n",
//				       posi.X(),posi.Y(),
//				       posf.X(),posf.Y());
	               addLink(cbNode(posi,wi,ci),cbNode(posf,wf,cf),dist);
	           }
		   
	           posi=corneri[ci]+(cornerf[cf]-corneri[ci]).normalize().rotate(-M_PI/2)*ROBOT_RADIUS;
	           posf=cornerf[cf]+(cornerf[cf]-corneri[ci]).normalize().rotate(-M_PI/2)*ROBOT_RADIUS;

	//	   fprintf(stderr,"testing 2 posi(%f,%f) posf(%f,%f)\n",
	//			       posi.X(),posi.Y(),
	//			       posf.X(),posf.Y());
                   if( lab->reachableRobot(posi, posf) ) {
	               dist=posi.distance(posf);
	       
//		       fprintf(stderr,"2 posi(%f,%f) posf(%f,%f)\n",
//				       posi.X(),posi.Y(),
//				       posf.X(),posf.Y());
	               addLink(cbNode(posi,wi,ci),cbNode(posf,wf,cf),dist);
	           }

		   // corners opened in opposite sens
		   
		   if(ROBOT_RADIUS<corneri[ci].distance(cornerf[cf])/2) {
                      double angle=acos(ROBOT_RADIUS/(corneri[ci].distance(cornerf[cf])/2));

	              posi=corneri[ci]+(cornerf[cf]-corneri[ci]).normalize().rotate(angle)*ROBOT_RADIUS;
	              posf=cornerf[cf]-(cornerf[cf]-corneri[ci]).normalize().rotate(angle)*ROBOT_RADIUS;

                      if( lab->reachableRobot(posi, posf) ) {
	                  dist=posi.distance(posf);
	          
//		          fprintf(stderr,"3 posi(%f,%f) posf(%f,%f)\n",
//		   		       posi.X(),posi.Y(),
//		   		       posf.X(),posf.Y());
	                  addLink(cbNode(posi,wi,ci),cbNode(posf,wf,cf),dist);
	              }

	              posi=corneri[ci]+(cornerf[cf]-corneri[ci]).normalize().rotate(-angle)*ROBOT_RADIUS;
	              posf=cornerf[cf]-(cornerf[cf]-corneri[ci]).normalize().rotate(-angle)*ROBOT_RADIUS;

                      if( lab->reachableRobot(posi, posf) ) {
	                  dist=posi.distance(posf);
	       
//		          fprintf(stderr,"4 posi(%f,%f) posf(%f,%f)\n",
//				       posi.X(),posi.Y(),
//				       posf.X(),posf.Y());
	                  addLink(cbNode(posi,wi,ci),cbNode(posf,wf,cf),dist);
	              }
		  }
		  
	       }
            }
	}
    }

    //link nodes in the same corner
//    fprintf(stderr,"start link nodes at same corner nnodes=%d\n",nodes.size());
    for(n1 = 0; n1 < nodes.size(); n1++)
        for(n2 = n1+1; n2 < nodes.size(); n2++)
		if(nodes[n1].wall()==nodes[n2].wall()
		   && nodes[n1].corner()==nodes[n2].corner()) {
			double dist=cornerPathDist(nodes[n1],nodes[n2]);
			addLink(nodes[n1],nodes[n2],dist);
			addLink(nodes[n2],nodes[n1],dist);
		}
}

/*! 
 * Links a node to nodes at the same corner.
 */
void cbGraph::linkToCornerNodes(cbNode node)
{
    unsigned int n,w,c;
    w=node.wall();
    c=node.corner();
    for(n = 0; n < nodes.size(); n++) {

            if(nodes[n].wall()==w
	       && nodes[n].corner()==c) {
		 //  fprintf(stderr,"adding link n=%d,wall=%d,corner=%d\n",
		//		    n,nodes[n].wall(),nodes[n].corner());
	            if(nodes[n].pos()==node.pos()) continue;

		    double dist=cornerPathDist(nodes[n],node);
		    
	            addLink(nodes[n],node,dist);
	            addLink(node,nodes[n],dist);
	    }
    }
}

/*! 
 * Determines distance between to nodes at the same corner.
 * The distance is calculated so that path is in the exterior of the corner.
 * The path is a section of a circunference with radius equal to robot radius.
 */
double cbGraph::cornerPathDist(cbNode node1,cbNode node2)
{
    unsigned int w,c;
    double dist=0.0; 
    double alpha,beta,gama;

    w=node1.wall();
    c=node1.corner();
    vector<cbPoint> &corners = lab->Wall(w)->Corners();

    assert(node2.wall()==w && node2.corner()==c);

    alpha=(node1.pos()-corners[c]).angle();
    beta=(node2.pos()-corners[c]).angle();
    if(c==0)
       gama=(corners[corners.size()-1]-corners[c]).angle();
    else
       gama=(corners[c-1]-corners[c]).angle();

    if(alpha>beta)
	    if(gama < alpha && gama > beta)
		 dist=(2*M_PI-alpha+beta)*ROBOT_RADIUS;  
            else dist=(alpha-beta)*ROBOT_RADIUS;
    else
	    if(gama < beta && gama > alpha)
		  dist=(2*M_PI-beta+alpha)*ROBOT_RADIUS; 
            else  dist=(beta-alpha)*ROBOT_RADIUS;
    
    if(dist<0.0) dist=0; // may happen because of errors in floating point
    return dist;
}

void cbGraph::addInitPoint(cbPoint &p)
{
    unsigned int w,c;
    double dist;
    cbPoint posf;

    //fprintf(stderr,"cbgraph::addInitPoint %.2f,%.2f\n", p.X(), p.Y());

    addInitNode(cbNode(p,MAXINT,MAXINT));

    // graph nodes are positioned at the distance of the 
    // robot radius with respect to some corner
    // The same corner may have several nodes (with diferrent
    // angles with respect to the corner)
    for(w = 0; w < lab->nWalls(); w++) {

        vector<cbPoint> &corner = lab->Wall(w)->Corners();

        for(c = 0; c < corner.size(); c++) {
          // fprintf(stderr,"w=%d c=%d convex=%d\n",
	//		   w,c,lab->Wall(w)->convexCorner(c));

	   if( ! lab->Wall(w)->convexCorner(c)) continue;

	   double angle=acos(ROBOT_RADIUS/p.distance(corner[c]));

	   posf=corner[c]+(p-corner[c]).normalize().rotate(angle)*ROBOT_RADIUS;

	 //  fprintf(stderr,"testing 1i p(%f,%f) posf(%f,%f)\n",
	//			       p.X(),p.Y(),
	//			       posf.X(),posf.Y());
           if( lab->reachableRobot(p, posf) ) {
	               dist=p.distance(posf);
	       
//		       fprintf(stderr,"new node 1i p(%f,%f) posf(%f,%f)\n",
//				       p.X(),p.Y(),
//				       posf.X(),posf.Y());
	               addLink(cbNode(p,MAXINT,MAXINT),cbNode(posf,w,c),dist);
		       linkToCornerNodes(cbNode(posf,w,c));
	   }

	   posf=corner[c]+(p-corner[c]).normalize().rotate(-angle)*ROBOT_RADIUS;

	   //fprintf(stderr,"testing 2i p(%f,%f) posf(%f,%f)\n",
	//			       p.X(),p.Y(),
	//			       posf.X(),posf.Y());
           if( lab->reachableRobot(p, posf) ) {
	               dist=p.distance(posf);
	       
//		       fprintf(stderr,"newnode 2i p(%f,%f) posf(%f,%f)\n",
//				       p.X(),p.Y(),
//				       posf.X(),posf.Y());
	               addLink(cbNode(p,MAXINT,MAXINT),cbNode(posf,w,c),dist);
		       linkToCornerNodes(cbNode(posf,w,c));
	   }
	}
    }
}

void cbGraph::addFinalPoint(unsigned int id, cbPoint &p)
{
    unsigned int w,c,i;
    double dist;
    cbPoint posi;

    addFinalNode(id,cbNode(p,MAXINT,MAXINT));

    // graph nodes are positioned at the distance of the 
    // robot radius with respect to some corner
    // The same corner may have several nodes (with diferrent
    // angles with respect to the corner)
    for(w = 0; w < lab->nWalls(); w++) {

        vector<cbPoint> &corner = lab->Wall(w)->Corners();

        for(c = 0; c < corner.size(); c++) {
         //  fprintf(stderr,"w=%d c=%d convex=%d\n",
	//		   w,c,lab->Wall(w)->convexCorner(c));

	   if( ! lab->Wall(w)->convexCorner(c)) continue;

	   double angle=acos(ROBOT_RADIUS/p.distance(corner[c]));

	   posi=corner[c]+(p-corner[c]).normalize().rotate(angle)*ROBOT_RADIUS;

	   cbPoint offset = (p-corner[c]).normalize().rotate(angle)*ROBOT_RADIUS;

	   //fprintf(stderr,"testing 1f1 c(%6.3f,%6.3f) angle=%6.1f offset(%6.3f,%6.3f)\n",
	//			       corner[c].X(),corner[c].Y(),
	//			       angle*180.0/M_PI,
	//			       offset.X(),offset.Y());
	 //  fprintf(stderr,"testing 1f posi(%6.3f,%6.3f) p(%6.3f,%6.3f)\n",
	//			       posi.X(),posi.Y(),
	//			       p.X(),p.Y());
           if( lab->reachableRobot(posi, p) ) {
	               dist=p.distance(posi);
	       
//		       fprintf(stderr,"new node 1f posi(%6.3f,%6.3f) p(%6.3f,%6.3f)\n",
//				       posi.X(),posi.Y(),
//				       p.X(),p.Y());
	               addLink(cbNode(posi,w,c),cbNode(p,MAXINT,MAXINT),dist);
		       linkToCornerNodes(cbNode(posi,w,c));
	   }

	   posi=corner[c]+(p-corner[c]).normalize().rotate(-angle)*ROBOT_RADIUS;

	  // fprintf(stderr,"testing 2f posi(%6.3f,%6.3f) p(%6.3f,%6.3f)\n",
	//			       posi.X(),posi.Y(),
	//			       p.X(),p.Y());
           if( lab->reachableRobot(posi, p) ) {
	               dist=p.distance(posi);
	       
//		       fprintf(stderr,"new node 2f posi(%6.3f,%6.3f) p(%6.3f,%6.3f)\n",
//				       posi.X(),posi.Y(),
//				       p.X(),p.Y());
	               addLink(cbNode(posi,w,c),cbNode(p,MAXINT,MAXINT),dist);
		       linkToCornerNodes(cbNode(posi,w,c));
	   }
	}
    }

    for(i=0;i<inits.size();i++)
	    if(lab->reachableRobot(inits[i].pos(),p))
	         addLink(inits[i],cbNode(p,MAXINT,MAXINT),inits[i].pos().distance(p));
}


void cbGraph::writeNodes(void)
{
	unsigned int n;
	for(n=0; n<nodes.size(); n++)
		fprintf(stderr,"%3d: node(%6.3f,%6.3f) wall=%2d corner=%2d\n",
				n,nodes[n].pos().X(),nodes[n].pos().Y(),
				nodes[n].wall(),nodes[n].corner());
}

void cbGraph::writeGraph(void)
{
	unsigned int n,l;
        FILE *fdebug=fopen("cbgraph.txt","w");
	for(n=0; n<nodes.size(); n++) {
		fprintf(fdebug,"%3d: node(%6.3f,%6.3f) wall=%2d corner=%2d\n",
				n,nodes[n].pos().X(),nodes[n].pos().Y(),
				nodes[n].wall(),nodes[n].corner());
		for(l=0;l<links[n].size();l++)
		    fprintf(fdebug,"   -> %d =%6.3f\n",
				    links[n].getNext(l),
				    links[n].getDist(l));
	}
        fclose(fdebug);
}
