using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace supermarkey
{
    class NoteBook:production
    {
        public NoteBook(int i,string n,double p):base(i,n,p)
	    {
		    this.id=i;
		    this.name=n;
		    this.price=p;
	    }
    }
}
