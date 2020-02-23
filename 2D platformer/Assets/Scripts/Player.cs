using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour
{
    [SerializeField] private Rigidbody2D _rigidbody2D;
    [SerializeField] private Animator _animator;
    [SerializeField] private ContactFilter2D _filter;

    [SerializeField] private bool _isLive;
    [SerializeField] private float _speed;
    [SerializeField] private float _jumpForce;
    [SerializeField] private string _leftRightTrigger;

    private bool _onGround;
    private int _direction;
    private readonly RaycastHit2D[] _results = new RaycastHit2D[1];
    private void Awake()
    {
        _isLive = true;
        _direction = 1;
    }

    private void Update()
    {
        if (_leftRightTrigger != "")
        {
            _animator.ResetTrigger(_leftRightTrigger);
        }
        if (_isLive && Input.anyKey)
        {
            if (Input.GetKey(KeyCode.A) || Input.GetKey(KeyCode.D))
            {

                if (Input.GetKey(KeyCode.D))
                {
                    _direction = 1;
                }
                if (Input.GetKey(KeyCode.A))
                {
                    _direction = -1;
                }
                var collisionsCount = _rigidbody2D.Cast(_direction * transform.right, _filter, _results, 0.3f);
                if (collisionsCount == 0)
                {
                    MoveSideways();
                }
            }
            if (Input.GetKeyDown(KeyCode.Space) && _onGround == true)
            {
                JumpSideways();
            }
        }
    }   

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.collider.GetComponent<BoxCollider2D>())
        {
            _onGround = true;
        }
    }

    private string ChooseSide(string triggerRight, string triggerLeft)
    {
        string resultTrigger = "";

        if (_direction == 1)
        {
            resultTrigger = triggerRight;
        }
        else if (_direction == -1)
        {
            resultTrigger = triggerLeft;
        }

        return resultTrigger;
    }
    private void MoveSideways()
    {
       _leftRightTrigger = ChooseSide("RunRight", "RunLeft");
       string trigger = ChooseSide("RunRight", "RunLeft");
        transform.Translate(_direction * _speed * Time.deltaTime, 0, 0);
       _animator.SetTrigger(_leftRightTrigger);
    }
    private void JumpSideways()
    {
        string trigger = ChooseSide("JumpRight", "JumpLeft");
        _rigidbody2D.AddForce(Vector2.up * _jumpForce);
        _onGround = false;
        _animator.SetTrigger(trigger);

    }

    public void DeathPlayer()
    {
        if (_isLive)
        {
            _isLive = false;
            _animator.SetTrigger("Death");
            Debug.Log("Вы мертвы");
        }
    }

}




