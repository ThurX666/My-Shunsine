
enum contactData 
{
	contactID,
	contactExists,
	contactName[32],
	contactNumber
};

new ContactData[MAX_PLAYERS][MAX_CONTACTS][contactData];
new ListedContacts[MAX_PLAYERS][MAX_CONTACTS];
