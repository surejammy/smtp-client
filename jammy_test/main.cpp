#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

using namespace std;


/**
 * The mailx context structure containing the parameters for setting up the
 * SMTP connection and sending the email.
 */
struct mailx{
  /**
   * Email subject line.
   */
  const char *subject;

  /**
   * Email body text.
   */
  char *body;

  /**
   * SMTP server name or IP address.
   */
  char *server;

  /**
   * SMTP server port number.
   */
  char *port;

  /**
   * SMTP account user name used for authenticating.
   */
  char *user;

  /**
   * SMTP account password used for authenticating.
   */
  char *pass;

  /**
   * From email address or name.
   */
  char *from;


  /**
   * Number of email addresses in @ref address_list.
   */
  size_t num_address;


  /**
   * Number of attachments in @ref attachment_list.
   */
  size_t num_attachment;
};


void
mailx_parse_smtp_option(struct mailx* mailx, const char *const option){

  int rc;

  rc = 0;

  char *token = NULL;
  char* src = NULL;
  if((src = strdup(option)) == NULL){
    printf("strdup: option: %s", option);
    return;
  }

    while((token = strsep(&src, "&")) != NULL){

        printf("to sep: %s\n", token);

        char *optdup = NULL;
        char *opt_key = NULL;
        char *opt_value = NULL;

        if((optdup = strdup(token)) == NULL){
            printf("strdup NULL: token: %s", token);
            continue;
        }

        if((opt_key = strtok(optdup, "=")) == NULL){
            printf("strtok: %s", optdup);
        }

        opt_value = strtok(NULL, "=");

        if(strcmp(opt_key, "smtp-security") == 0){
            if(strcmp(opt_value, "none") == 0){
              printf("mailx->connection_security = SMTP_SECURITY_NONE\n");
            }
            else if(strcmp(opt_value, "tls") == 0){
              printf("mailx->connection_security = SMTP_SECURITY_TLS\n");
            }
            else if(strcmp(opt_value, "starttls") == 0){
              printf("mailx->connection_security = SMTP_SECURITY_STARTTLS\n");
            }
            else{
              rc = -1;
              printf("smtp-security invalid\n");
            }
        }
        else if(strcmp(opt_key, "smtp-auth") == 0){
            if(strcmp(opt_value, "none") == 0){
              printf("mailx->auth_method = SMTP_AUTH_NONE\n");
            }
            else if(strcmp(opt_value, "plain") == 0){
              printf("mailx->auth_method = SMTP_AUTH_PLAIN\n");
            }
            else if(strcmp(opt_value, "login") == 0){
              printf("mailx->auth_method = SMTP_AUTH_LOGIN\n");
            }
            else if(strcmp(opt_value, "cram-md5") == 0){
              printf("mailx->auth_method = SMTP_AUTH_CRAM_MD5\n");
            }
            else{
              printf("smtp-auth value invalid\n");
              rc = -1;
              continue;
            }
        }
        else if(strcmp(opt_key, "smtp-flag") == 0){
            if(strcmp(opt_value, "debug") == 0){
              printf("mailx->smtp_flags |= SMTP_DEBUG\n");
            }
            else if(strcmp(opt_value, "no-cert-verify") == 0){
              printf("mailx->smtp_flags |= SMTP_NO_CERT_VERIFY\n");
            }
            else{
              printf("mailx->smtp_flags invalid\n");
              rc = -1;
            }
        }
        else if(strcmp(opt_key, "smtp-server") == 0){
            if((mailx->server = strdup(opt_value)) == NULL){
              printf("smtp-server strdup failed\n");
            }
        }
        else if(strcmp(opt_key, "smtp-port") == 0){
            if((mailx->port = strdup(opt_value)) == NULL){
              printf("smtp-port strdup failed\n");
            }
        }
        else if(strcmp(opt_key, "smtp-user") == 0){
            if((mailx->user = strdup(opt_value)) == NULL){
              printf("smtp-user strdup failed\n");
            }
        }
        else if(strcmp(opt_key, "smtp-pass") == 0){
            if((mailx->pass = strdup(opt_value)) == NULL){
              printf("smtp-pass strdup failed\n");
            }
        }
        else if(strcmp(opt_key, "smtp-from") == 0){
            if((mailx->from = strdup(opt_value)) == NULL){
              printf("smtp-from strdup failed\n");
            }
        }
        else{
            printf("%s not support\n", opt_key);
            rc = -1;
        }

        free(optdup);

        if(rc < 0){
            printf("invalid argument: %s", option);
        }
    }

    free(src);
    return;

}


void print_mailx(struct mailx* m) {

    //printf("smtp-security:%s\n", m->connection_security);
    printf("smtp-pass:%s\n", m->pass);
    printf("smtp-from:%s\n", m->from);
   
    return;
}


int main()
{
    cout << "Hello world!" << endl;

    struct mailx* mailx = new struct mailx();

    char option[] = "smtp-security=tls&smtp-pass=1234&smtp-from=jammyxu@yunpiaoer.com";
    mailx_parse_smtp_option(mailx, option);

    print_mailx(mailx);
    return 0;
}
