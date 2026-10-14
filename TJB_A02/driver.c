#include <stdio.h>
#include <string.h>
#include "user.h"


int main(void) {
	struct User * head=NULL;
	head = add(head, "rob");
	head = add(head, "hanif");
	head = add(head, "gahyun");
	head = add(head, "matt");
	head = add(head, "sumita");
	head = add(head, "james");

	//chain order: james -> sumita -> matt -> gahyun -> hanif -> rob
	struct User* sumita = head->next;
	struct User* matt = head->next->next;

	//print the log to check order, names, times, hashes
	printf("\n*** Access log ***\n");
	printLog(head);

	//untouched chain should pass
	printf("\n*** Untouched chain ***\n");
	verify(head);

	//change matt's username: should fail
	printf("\n*** matt -> Matt ***\n");
	matt->Username[0] = 'M';
	verify(head);
	matt->Username[0] = 'm';  //undo

	//change matt's timestamp: should fail
	printf("\n*** matt's time + 1 hour ***\n");
	matt->loginTime += 3600;
	verify(head);
	matt->loginTime -= 3600;  //undo

	//remove matt from the chain: should fail
	printf("\n*** Remove matt ***\n");
	sumita->next = matt->next;
	verify(head);
	sumita->next = matt;  //undo

	//change matt & recalculate the hash that checks matt: should fail
	printf("\n*** Change matt and re-hash ***\n");
	matt->Username[0] = 'M';
	generateDigest(&(sumita->hash), matt);
	verify(head);
	matt->Username[0] = 'm';  //undo
	generateDigest(&(sumita->hash), matt);

	//second login for rob, should appear at the top of the log
	printf("\n*** rob logs in again ***\n");
	head = add(head, "rob");
	printLog(head);
	verify(head);

	//change the newest block
	printf("\n*** Change newest block (rob -> Rob) ***\n");
	head->Username[0] = 'R';
	verify(head);
	head->Username[0] = 'r';  //undo
}