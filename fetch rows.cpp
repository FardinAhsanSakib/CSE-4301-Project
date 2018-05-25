#include <stdio.h>
#include <SQLAPI.h>
int main(int argc, char* argv[])
{
    SAConnection con;
    SACommand cmd(
        &con,
        "Select fid, fvarchar20 from test_tbl");

    try
    {

        con.Connect("iut", "tester", "tester", SA_Oracle_Client);

        // Select from our test table
        cmd.Execute();
        // fetch results row by row and print results
        while(cmd.FetchNext())
        {
            printf("Row is now fetched: fid = %ld, fvarchar20 = '%s'\n",
                cmd.Field("fid").asLong(),
                (const char*)cmd.Field("fvarchar20").asString());
        }

        con.Commit();

        printf("Rows  are selected!\n");
    }
    catch(SAException &x)
    {

        try
        {

            con.Rollback();
        }
        catch(SAException &)
        {
        }
        printf("%s\n", (const char*)x.ErrText());
    }

    return 0;
}
