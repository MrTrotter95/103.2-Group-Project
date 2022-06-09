#include "main.h"
#include "feedback.h"


/* START OF FEEDBACK PSEUDO CODE FOR ADMIN 
    •Create function: Feedback()
    •Display Options to user Complaint/Compliment/General
    •Display all feedback from parents/user.
    •Potentially include  bool = hasContacted;  change this value to true when a parent submits a complaint
    •Allow user to select one and change value to actioned.
    •Potentially include bool = hasContactedResolved; change this value to true when a admin resolves a complaint.
In simple terms, I want to have a function that will remove a compaint or change it to resolved so it doesn't show up in the list anymore
We will still have a record of a compaint, but it will be marked as resolved.
    •User can exit at any time back to their logged in menu. 
END OF FEEDBACK PSEUDO CODE FOR ADMIN */

/* START OF FEEDBACK PSEUDO CODE FOR PARENT
    Create functiin: ContactUs();
    display options of the types of contact a user can make General Contact / Complaint / Compliment
    Create three functions: GeneralContact(), Complaint(), Compliment().
    These three functions just display a message.
    Allow user to go back to the main menu.
END OF FEEDBACK PSEUDO CODE FOR PARENT */

/*Questions
 1) Flow Chart doesn't really make sense. A Admin can display all complaints/feedback, select and mark one as resolved.
 but a parent doesn't get to submit or type a complaint/ compliement? Do we want to include this, and have userMessage a member inside the USER class?
 
 Do allow them to complaint.

*/

/*Start of Feedback functionality*/
void feedbackMain()
{
    cout << "feedback.cpp connected..\n";
}